/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_input_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				backspace(t_input **input, t_para **glob)
{
	if ((*glob)->cursor->posy - 1 == (*glob)->cursor->ymax)
	{
		ft_putendl_fd("backspace_last 1", 2);
		backspace_last(input, glob);
	}
	else if ((*glob)->cursor->posy - 1 < (*glob)->cursor->ymax)
		backspace_inside(input, glob);
	if ((*glob)->cursor->ymax < (*glob)->term->size[0] - (*glob)->prompt_s)
	{
		(*glob)->cursor->ymax--;
		ft_putstr_fd("inferieur", 2);
	}
	else
	{
		ft_putstr_fd("modify last", 2);
		modify_ymax_to_last(glob, &(*glob)->cursor, -1);
	}
	(*glob)->total_c -= 1;

}
void				backspace_last(t_input **input, t_para **glob)
{
	t_input			*ptr;
	int				i;

	i = 0;
	ptr = *input;
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->prev)
		ptr->prev->next = NULL;
	ft_putendl_fd("backspace_last 2", 2);
	free(ptr);
	if ((*glob)->cursor->posy == 1)
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		while (i < (*glob)->term->size[0]) // a voir le - 1
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			//ft_putnbr_fd(i, 2);
			i++;
		}
	}
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	ft_putchar_fd(' ', (*glob)->fd);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	(*glob)->cursor->posy--;
	if ((*glob)->cursor->posy == 1)
		*input = NULL;
}

void				backspace_inside(t_input **input, t_para **glob)
{
	t_input			*ptr;
	t_input			*tmp;
	int				i;
	int				x;
	int				y;
	int				prompt;
	int				position;

	if ((*glob)->cursor->posx == 0)
		position = (*glob)->cursor->posy;
	else
	{
		position = (*glob)->term->size[0] - (*glob)->prompt_s;//verfier le dernier charactere
		position += (*glob)->cursor->posy;
		position += (((*glob)->cursor->posx - 1) * (*glob)->term->size[0]);//verfier le dernier charactere
	}
	ptr = *input;
	while (ptr)
	{
		if (ptr->pos[0] == 0 && position == 2)
		{
			ft_putstr_fd("inside first", 2);

			tmp = ptr->next;
			free(ptr);
			*input = tmp;
			(*input)->prev = NULL;
			break ;
		}
		else if (ptr->next && ptr->next->pos[0] == position - 1)
		{
			ft_putstr_fd("inside pos - 1", 2);

			tmp = ptr->next;
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			free(ptr);
			break ;
		}
		else
			ft_putstr_fd("oyeee", 2);

		ptr = ptr->next;
	}

	x = 0;
	ptr = *input;
	while(ptr)
	{
		ptr->pos[0] = x++;
		ptr = ptr->next;
	}

	y = (*glob)->cursor->posy;
	x = (*glob)->cursor->posx;
	prompt = (*glob)->prompt_s;
	while (y > 1)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		y--;
	}
	while (prompt > 0)
	{	
		if (x > 0)
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
		prompt--;
	}
	while (x > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		x--;
	}


	ptr = *input;
	y = (*glob)->prompt_s;
	while (ptr)
	{
		if (ptr->selected == 1)//faire une fonction
		{
			ft_putstr_fd("\x1b[32m", (*glob)->fd);
			ft_putchar_fd(ptr->c, (*glob)->fd);
			ft_putstr_fd("\x1b[0m", (*glob)->fd);
		}
		else 
			ft_putchar_fd(ptr->c, (*glob)->fd);
		if (y <= (*glob)->term->size[0])
		{
			y++;
			if (y == (*glob)->term->size[0])
			{
				x++;
				y = 1;
			}
		}
		ptr = ptr->next;
	}
	ft_putchar_fd(' ', (*glob)->fd);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
//	y++;
	if (y > (*glob)->term->size[0])
	{
		y = 1;
		x++;
	}
	// y ++;
	// if (y > (*glob)->term->size[0])
	// {
	// 	y = 0;
	// 	x++;
	// }
	int tmpy;

	while (x > (*glob)->cursor->posx)
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		x--;
	}

	tmpy = (*glob)->cursor->posy - 1;
	if ((*glob)->cursor->posx == 0)
	{
		tmpy += (*glob)->prompt_s;
	}
	if (y > tmpy)
	{
		while (y > tmpy)
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			y--;
		}
	}
	else if (y < tmpy)
	{
		while (y < tmpy)
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			y++;
		}
	}

	(void)i;
	(*glob)->cursor->posy--;
}
