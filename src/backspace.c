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
	if ((*glob)->cursor->posy == (*glob)->total_c)
		backspace_last(input, glob);
	else if ((*glob)->cursor->posy < (*glob)->total_c)
		backspace_inside(input, glob);
	(*glob)->total_c -= 1;

}
void				backspace_last(t_input **input, t_para **glob)
{
	t_input			*ptr;

	ptr = *input;
	while (ptr->next)
		ptr = ptr->next;
	if ((*glob)->cursor->posy != 1)
		ptr->prev->next = NULL;
	(*glob)->cursor->posy--;
	free(ptr);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	ft_putchar_fd(' ', (*glob)->fd);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	if ((*glob)->cursor->posy == 0)
		*input = NULL;
}

void				backspace_inside(t_input **input, t_para **glob)
{
	t_input			*ptr;
	t_input			*tmp;
	int				i;
	int				x;

	ptr = *input;
	i = (*glob)->cursor->posy;
	while (ptr)
	{
		if (i == 1 && ptr->pos[0] == 0)
		{
			tmp = ptr->next;
			tmp->prev = NULL;
			free(ptr);
			*input = tmp;
			break ;
		}
		else if (ptr->next && ptr->next->pos[0] == i)
		{
			ptr->prev->next = ptr->next;//error
			ptr->next->prev = ptr->prev;
			free(ptr);
			break;
		}
		ptr = ptr->next;
	}
	x = 0;
	ptr = *input;
	while(ptr)
	{
		ptr->pos[0] = x++;
		ptr = ptr->next;
	}
	while (i > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		i--;
	}
	ptr = *input;
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
		i++;
		ptr = ptr->next;
	}
	ft_putchar_fd(' ', (*glob)->fd);
	i++;
	i++;
	while (i > (*glob)->cursor->posy)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		i--;
	}
	(*glob)->cursor->posy--;
}
