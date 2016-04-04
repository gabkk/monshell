/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		back_del_maillon(t_para **glob, t_input **input, int position)
{
	t_input			*tmp;
	t_input			*ptr;

	ptr = *input;
	while (ptr)
	{
		if (ptr->pos[0] == 0 && position == 2)
		{
			ft_putstr_fd("inside first", 2);

			tmp = ptr->next;
			unset_quoting(&(*glob)->quoting, ptr->c);
			free(ptr);
			*input = tmp;
			// if ((*input)->prev)
			// 	(*input)->prev = NULL;
			break ;
		}
		else if (ptr->next && ptr->next->pos[0] == position - 1)
		{
			ft_putstr_fd("inside pos -1 ", 2);

			tmp = ptr->next;
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			unset_quoting(&(*glob)->quoting, ptr->c);
			free(ptr);
			break ;
		}
		// else
		// 	ft_putstr_fd("oyeee", 2);

		ptr = ptr->next;
	}
}

void				back_redraw(t_para **glob, t_input **input)
{
	t_input			*ptr;
	int				x;
	int				y;

	x = 0;
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
		if (y < (*glob)->term->size[0])
		{
			y++;
		}
		if (y == (*glob)->term->size[0])
		{
			x++;
			y = 0;
		}
		ptr = ptr->next;
	}
	ft_putchar_fd(' ', (*glob)->fd);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	back_reposition(glob, x ,y);
}

void			back_reposition(t_para **glob, int x, int y)
{
	while (x > 0) //modifier printlst input comme ici
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		x--;
	}
	if (y < (*glob)->prompt_s)
	{
		while (y < (*glob)->prompt_s) // -1 pour aller apres prompt_pos
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			y++;
		}
	}
	else if (y > (*glob)->prompt_s)
	{
		while (y > (*glob)->prompt_s) // +1 pour aller apres prompt_pos
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			y--;
		}
	}
}