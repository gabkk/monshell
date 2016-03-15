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
		(*input)->c = buf;
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
	t_input			*ptr;
	t_input			*newm;

	newm = init_lst_input();
	ptr = *input;
	ptr->pos[0] = i + 1;
	newm->next = ptr;
	ptr->prev = newm;
	newm->pos[0] = i;
	newm->c = buf;
	*input = newm;
}

void				add_inside_input(t_input **input, char buf, int i)
{
	t_input			*ptr;
	t_input			*newm;

	newm = init_lst_input();
	ptr = *input;
	if (i == 0)
		set_first_input(input, buf, i);
	while (ptr)
	{
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
	newmaillon->pos[0] = 0;
	newmaillon->pos[1] = 0;
	newmaillon->prev = NULL;
	newmaillon->next = NULL;
	return (newmaillon);
}

void				print_lst_input(t_input **input, t_para **glob)
{
	t_input 		*ptr;
	int				i;

	i = (*glob)->cursor[0];
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
	while (i > (*glob)->cursor[0] + 1)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		i--;
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
	(*glob)->cmd = (char *)malloc(sizeof(char) * i);
	ptr = *input;
	i = 0;
	while (ptr)
	{
		(*glob)->cmd[i] = ptr->c;
		i++;
		ptr = ptr->next;
	}
	(*glob)->cmd[i] = '\0';
	delete_lst_input(input);
	(*glob)->term->action = 1;
	ft_putchar_fd('\n', (*glob)->fd);
}

void				delete_lst_input(t_input **input)
{
	t_input			*ptr;
	t_input			*tmp;

	ptr = *input;
	if (!ptr)
		return ;
	while (ptr->next)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*input = NULL;
}
