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

void				add_to_lst_input(t_input **input, char buf, int i)
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
	newm->index = i;
	newm->c = buf;
}

t_input				*init_lst_input()
{
	t_input			*newmaillon;

	newmaillon = (t_input *)malloc(sizeof(t_input));
	if (!newmaillon)
		return (NULL);
	newmaillon->c = 0;
	newmaillon->index = 0;
	newmaillon->pos[0] = 0;
	newmaillon->pos[1] = 0;
	newmaillon->prev = NULL;
	newmaillon->next = NULL;
	return (newmaillon);
}

void				print_lst_input(t_input **input, t_para **glob)
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
