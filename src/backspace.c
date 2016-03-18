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
	if ((*glob)->cursor[0] == (*glob)->total_c)
		backspace_last(input, glob);
	else if ((*glob)->cursor[0] < (*glob)->total_c)
		backspace_inside(input, glob);
	(*glob)->total_c -= 1;

}
void				backspace_last(t_input **input, t_para **glob)
{
	t_input			*ptr;

	ptr = *input;
	while (ptr->next)
		ptr = ptr->next;
	if ((*glob)->cursor[0] != 1)
		ptr->prev->next = NULL;
	(*glob)->cursor[0]--;
	free(ptr);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	ft_putchar_fd(' ', (*glob)->fd);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	if ((*glob)->cursor[0] == 0)
		*input = NULL;
}

void				backspace_inside(t_input **input, t_para **glob)
{
	t_input			*ptr;
	t_input			*tmp;
	int				i;
	int				x;

	ptr = *input;
	i = (*glob)->cursor[0];
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
	// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	// ft_putchar_fd(' ', (*glob)->fd);
	// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);

	// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);

	// REPLACER LE DERNIER CHAR PAR UN ESPACE
	// REDRAW
	while (i > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		i--;
	}
	ptr = *input;
	while (ptr)
	{
		ft_putchar_fd(ptr->c, (*glob)->fd);
		i++;
		ptr = ptr->next;
	}
	ft_putchar_fd(' ', (*glob)->fd);
	i++;
	i++;
	while (i > (*glob)->cursor[0])
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		i--;
	}
	(*glob)->cursor[0]--;



	// if ((*glob)->cursor[0] != 1)
	// 	ptr->prev->next = NULL;
	// (*glob)->cursor[0]--;
	// free(ptr);
	// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	// ft_putchar_fd(' ', (*glob)->fd);
	// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	// if ((*glob)->cursor[0] == 0)
	// 	*input = NULL;

}
