/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cursor_up(t_para **glob)
{
	int		tmp;

	tmp = 0;
	if ((*glob)->cursor->prev)
	{
		if ((*glob)->cursor->prev->posx == 0)
		{
			if ((*glob)->cursor->posy <= (*glob)->prompt_s)
			{
				while ((*glob)->cursor->posy <= (*glob)->prompt_s)
				{
					ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
					(*glob)->cursor->posy++;
				}
				(*glob)->cursor->posy = 1;
				(*glob)->cursor = (*glob)->cursor->prev;
				(*glob)->cursor->posy = 1;
			}
			else
			{
				tmp = (*glob)->cursor->posy;
				(*glob)->cursor->posy = 1;
				(*glob)->cursor = (*glob)->cursor->prev;
				(*glob)->cursor->posy = tmp - (*glob)->prompt_s;
			}
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		}
		else
		{
			tmp = (*glob)->cursor->posy;
			(*glob)->cursor->posy = 1;
			(*glob)->cursor = (*glob)->cursor->prev;
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);	
			(*glob)->cursor->posy = tmp;
		}
	}
}

void		cursor_down(t_para **glob)
{
	int		tmp;

	tmp = 0;
	if ((*glob)->cursor->next)
	{
		if ((*glob)->cursor->posx == 0)
			tmp = (*glob)->cursor->posy + (*glob)->prompt_s;
		else
			tmp = (*glob)->cursor->posy;
		(*glob)->cursor->posy = (*glob)->cursor->ymax + 1;
		(*glob)->cursor = (*glob)->cursor->next;
		if (tmp < (*glob)->cursor->ymax)
			(*glob)->cursor->posy = tmp;
		else
		{
			if ((*glob)->cursor->ymax == 0)
				(*glob)->cursor->posy = 1;
			else
				(*glob)->cursor->posy = (*glob)->cursor->ymax;
			tmp = (*glob)->cursor->ymax;
		}
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);	
		while (tmp > 1)
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			tmp--;
		}
	}
}

void		cursor_word_left(t_para **glob, t_input **input)
{
	int		value;

	value = 0;
	if (!*input)
		return ;
	if ((value = cursor_find_left(glob, input)) == -1)
	{
		cursor_pos_init(glob);
		while ((*glob)->cursor->prev)
			(*glob)->cursor = (*glob)->cursor->prev;
		(*glob)->cursor->posy = 1;
	}
	else
		position_cursor(glob, value);
}

int			cursor_find_left(t_para **glob, t_input **input)
{
	t_input		*ptr;
	int			position;

	ptr = *input;
	position = get_input_pos(glob) - 1;
	while (ptr)
	{
		if (ptr->pos[0] == position - 1)
			break ;
		ptr = ptr->next;
	}
	while (ptr)
	{
		if (ptr->c == ' ')
			return (ptr->pos[0] + 1);
		ptr = ptr->prev;
	}
	return (-1);
}

void		cursor_word_right(t_para **glob, t_input **input)
{
//	int		value;

//	value = 0;
	if (!*input)
		return ;
	cursor_find_right(glob, input);
	// if ((value = cursor_find_right(glob, input)) == -1)
	// {
	// 	ft_putendl_fd("Ya -1 : ", 2);//debug
	// 	ft_putendl_fd("total_c : ", 2);//debug
	// 	ft_putnbr_fd((*glob)->total_c, 2);//debug
	// 	position_cursor(glob, (*glob)->total_c);
	// }
	// else
	// 	position_cursor(glob, value);
	// 	ft_putstr_fd("value", 2);//debug
	// 	ft_putnbr_fd(value, 2);//debug
}

void			cursor_find_right(t_para **glob, t_input **input)
{
	t_input		*ptr;
	int			position;
	int			tmp;

	tmp = 0;
	ptr = *input;
	position = get_input_pos(glob) - 1;
	while (ptr)
	{
		if (ptr->pos[0] == position)
		{
			break ;
		}
		ptr = ptr->next;
	}
	if (!ptr)
		return ;
	if (ptr->c == ' ' && ptr->next)//a caller
		ptr = ptr->next;
	if((*glob)->cursor->posx == 0)
		tmp = (*glob)->prompt_s;
	tmp += (*glob)->cursor->posy;
	while (ptr)
	{
		if (ptr->c == ' ')
		{
			// ft_putendl_fd("GOT ONE : ", 2);//debug
			// ft_putnbr_fd(ptr->pos[0], 2);//debug
			// //return (ptr->pos[0] + 1);
			if (ptr->next)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
				ptr = ptr->next;
			}
			break ;
		}
		else
		{
			if (tmp == (*glob)->term->size[0] && (*glob)->cursor->next)
			{
				ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
				(*glob)->cursor = (*glob)->cursor->next;
				(*glob)->cursor->posy = 0;
				tmp = 0;
			}
			else
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor->posy++;
			tmp++;
		}
		ptr = ptr->next;
	}
//	return (-1);
}

void			cursor_home_end(t_para **glob, t_input **input, char buff)
{
	if (buff == 'H')
		cursor_home(glob, input);
	else if (buff == 'F')
		cursor_end(glob, input);
}

void			cursor_end(t_para **glob, t_input **input)
{//meme fonction que cursor_word_right le signe change
	t_input		*ptr;
	int			position;
	int			tmp;

	tmp = 0;
	ptr = *input;
	position = get_input_pos(glob) - 1;
	while (ptr)
	{
		if (ptr->pos[0] == position)
		{
			break ;
		}
		ptr = ptr->next;
	}
	if (!ptr)
		return ;
	if (ptr->c == '\n' && ptr->next)//a caller
		ptr = ptr->next;
	if((*glob)->cursor->posx == 0)
		tmp = (*glob)->prompt_s;
	tmp += (*glob)->cursor->posy;
	while (ptr)
	{
		if (ptr->c == '\n')
		{
			if (ptr->next)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
				ptr = ptr->next;
			}
			break ;
		}
		else
		{
			if (tmp == (*glob)->term->size[0] && (*glob)->cursor->next)
			{
				ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
				(*glob)->cursor = (*glob)->cursor->next;
				(*glob)->cursor->posy = 0;
				tmp = 0;
			}
			else
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor->posy++;
			tmp++;
		}
		ptr = ptr->next;
	}
}

void			cursor_home(t_para **glob, t_input **input)
{
	int		value;

	value = 0;
	if (!*input)
		return ;
	if ((value = cursor_find_home(glob, input)) == -1)
	{
		cursor_pos_init(glob);
		while ((*glob)->cursor->prev)
			(*glob)->cursor = (*glob)->cursor->prev;
		(*glob)->cursor->posy = 1;
	}
	else
		position_cursor(glob, value);
}

int			cursor_find_home(t_para **glob, t_input **input)
{
	t_input		*ptr;
	int			position;

	ptr = *input;
	position = get_input_pos(glob) - 1;
	while (ptr)
	{
		if (ptr->pos[0] == position - 1)
			break ;
		ptr = ptr->next;
	}
	while (ptr)
	{
		if (ptr->c == '\n')
			return (ptr->pos[0] + 1);
		ptr = ptr->prev;
	}
	return (-1);
}
