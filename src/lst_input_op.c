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

void				add_back_input(t_input **input, char buf, int i)
{
	t_input			*ptr;
	t_input			*newm;
	
	newm = init_lst_input();
	if (!*input)
	{
		*input = newm;
		newm->c = buf;//(*input)->c
		newm->pos[0] = i;
		return;
	}
	ptr = *input;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = newm;
	newm->prev = ptr;
	newm->pos[0] = i;
	newm->c = buf;
}

void				set_first_input(t_input **input, char buf, int i)
{
	t_input			*newm;
	t_input			*ptr;

	(void)i;
	newm = init_lst_input();
	newm->next = *input;
	(*input)->prev = newm;
	*input = newm;
	newm->pos[0] = 0;
	newm->c = buf;
	newm->selected = 0;
	newm->next->pos[0] = 1;
	ptr = *input;
	while (ptr)
	{
		if (ptr->pos[0] > 0)
			ptr->pos[0] = ptr->prev->pos[0] + 1;
		ptr = ptr->next;
	}
}

void				add_inside_input(t_input **input, char buf, int i)
{
	t_input			*ptr;
	t_input			*newm;

	if (i == 1)
	{
		set_first_input(input, buf, i);
		return ;
	}
	i--; //car input->pos et cursor pos sont diff
	newm = init_lst_input();
	ptr = *input;
	while (ptr)
	{
//		ft_putnbr_fd(ptr->pos[0], 2);

		if (ptr->pos[0] == i)
		{
			ptr->pos[0] = i + 1;
			ptr->prev->next = newm;
			newm->prev = ptr->prev;
			newm->next = ptr;
			ptr->prev = newm;
			newm->pos[0] = i;
			newm->c = buf;
		}
		else if (ptr->pos[0] > i)
			ptr->pos[0] = ptr->prev->pos[0] + 1;
		ptr = ptr->next;
	}
}

t_input				*init_lst_input()
{
	t_input			*newmaillon;

	newmaillon = (t_input *)malloc(sizeof(t_input));
	if (!newmaillon)
		return (NULL);
	newmaillon->c = 0;
	newmaillon->selected = 0;
	newmaillon->pos[0] = 0;
	newmaillon->pos[1] = 0;
	newmaillon->prev = NULL;
	newmaillon->next = NULL;
	return (newmaillon);
}

void				print_lst_input(t_input **input, t_para **glob)
{
	t_input 		*ptr;
	int				x;
	int				y;
	int				prompt;

//pas ok

	y = (*glob)->cursor->posy - 1;
	x = (*glob)->cursor->posx;
	prompt = (*glob)->prompt_s;
	while (y > 1)//fonction dupplique voir cursor_pos_init
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
	(void)ptr;
	(void)input;


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
			if (y == (*glob)->term->size[0])
			{
				x++;
				y = 0;
			}
			y++;
			// ft_putnbr_fd(y, 2);
			// ft_putchar_fd('-', 2);

		}
		ptr = ptr->next;
	}


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
	if (y > tmpy) //fonction dupplique
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


}

void				save_cmd(t_input **input, t_para **glob)
{
	t_input 		*ptr;
	int 			i;

	i = 0;
	ptr = *input;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	if (((*glob)->cmd = (char *)malloc(sizeof(char) * i + 1)) == NULL)
		return ;
	ptr = *input;
	i = 0;
	while (ptr)
	{
		(*glob)->cmd[i] = ptr->c;
		i++;
		ptr = ptr->next;
	}
	(*glob)->cmd[i] = '\0';
	(*glob)->term->action = 1;
	ft_putchar_fd('\n', (*glob)->fd);
}

void				delete_lst_input(t_input **input)
{
	t_input			*ptr;
	t_input			*tmp;

	ptr = *input;
	if (!ptr || !*input)
		return ;
	while (ptr->next) //ptr->next
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	free(ptr);// a voir
	*input = NULL;
}
