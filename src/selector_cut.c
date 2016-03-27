/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_cut.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					free_input_copy_buff(t_para **glob, t_input **input)
{
	t_input			*ptr;
	t_input			*tmp;
	int				i;
	int				position_f;

	position_f = -1;
	i = 0;
	ptr = *input;
	while (ptr)
	{
		if (ptr->selected == 1)
		{
			if (position_f == -1)
				position_f = ptr->pos[0];
			ptr->selected = 0;
			add_back_input(&(*glob)->copy, ptr->c, i);
			if (ptr->pos[0] == 0 && ptr->next)
			{
				tmp = ptr->next;
				tmp->pos[0] = 0;
				tmp->prev = NULL;
				free(ptr);
				*input = tmp;
				ptr = *input;
			}
			else if (!ptr->next)
			{
				if (ptr->prev)
					ptr->prev->next = NULL;
				free(ptr);
				if (!ptr->prev)
				{
					ptr = NULL;
					*input = ptr;
				}
			}
			else if (ptr->next)
			{
				tmp = ptr->prev;
				ptr->prev->next = ptr->next;//error
				ptr->next->prev = ptr->prev;
				free(ptr);
				ptr = tmp;
			}
			//(*glob)->cursor->ymax--;
			(*glob)->total_c--;
		}
		else
			ptr = ptr->next;
	}
	return (position_f);
}