/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mode_selector(t_para **glob)
{
	char			buff[3];
	int  			ret;

	ft_bzero(buff, 3);
	if ((ret = read(0, buff, 3)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	if (buff[2] == 'A')
		(*glob)->selector = 1;
	else if (buff[2] == 'B')
		(*glob)->selector = 0;	
}

void				set_selector(t_para **glob, t_input **input, int index, int direction)
{
	t_input 		*ptr;

	ptr = *input;
	while (ptr)
	{
		if (ptr->pos[0] == index)
		{
			if (direction == 1 && ptr->selected == 0)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[32m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 1;
			}
			else if (direction == 1 && ptr->selected == 1)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 0;
			}
			else if (direction == -1 && ptr->selected == 0)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[32m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 1;
			}
			else if (direction == -1 && ptr->selected == 1)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 0;
			}
		}
		ptr = ptr->next;
	}
}

void				selector_action(t_para **glob, t_input **input, int buff)
{
	t_input			*ptr;
	int				i;
	int				j;

	j = 0;
	i = 0;
	if (buff == 'c')
	{
		ptr = *input;
		if ((*glob)->copy)
			delete_lst_input(&(*glob)->copy);
		while (ptr)
		{
			if (ptr->selected == 1)
			{
				//ft_putchar_fd(ptr->c, (*glob)->fd);
				add_back_input(&(*glob)->copy, ptr->c, i);
				i++;
			}
			ptr = ptr->next;
		}
		(*glob)->selector = 0;
	}
	else if (buff == 'x')
	{
		ft_putstr_fd("cut", (*glob)->fd);
	}
	else if (buff == 'v')
	{
		if ((*glob)->copy)//(*glob)->copy)
		{
			ptr = (*glob)->copy;//(*glob)->copy;
			j = (*glob)->cursor[0];
			while (ptr)
			{
				ft_putchar_fd(ptr->c, (*glob)->fd);
				if (/*(*glob)->cursor[0]*/j == (*glob)->total_c)
				{
					add_back_input(input, ptr->c, (*glob)->total_c);
				}
				else
					add_inside_input(input, ptr->c, j/*(*glob)->cursor[0]*/);
				//(*glob)->cursor[0]++;
				
				(*glob)->total_c++;
				j++;
				ptr = ptr->next;
			}

			if (/*(*glob)->cursor[0]*/j != (*glob)->total_c)
			{
				ptr = *input;
				while (ptr)
				{
					if (ptr->pos[0] >= j)
					{
						ft_putchar_fd(ptr->c, (*glob)->fd);
						j++;
					}
					ptr = ptr->next;
				}
			}
			while (j > (*glob)->cursor[0])
			{
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				j--;
			}
			(*glob)->selector = 0;
		}
	}
}