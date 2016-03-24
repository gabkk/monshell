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

void				modify_ymax_to_last(t_para **glob, t_cursor **cursor, int value)
{
	t_cursor		*ptr;
	t_cursor		*newm;
	int				tmp;

	tmp = 0;
	ptr = *cursor;
	while (ptr->next)
	{
		//ft_putstr_fd("yO", 2);
		ptr = ptr->next;
	}
	if (value == 1)
	{
		if ((*glob)->cursor->posx == 0 && ptr->posx == 0)
			tmp += (*glob)->prompt_s;
		tmp += ptr->ymax + 1;
		if (tmp > (*glob)->term->size[0])
		{
			newm = init_cursor();
			ptr->next = newm;
			newm->prev = ptr;
			newm->ymax++;
			newm->posx = ptr->posx + 1;
		}
		else
			ptr->ymax++;
	}
	else if (value == -1)
	{
//		tmp += ptr->ymax + 1;
		if (ptr->posx > 0 && ptr->ymax == 1)
		{
			ptr->prev->next = NULL;
			ptr->prev->ymax--;
			free(ptr);
		ft_putstr_fd("freeptr", 2);
		}
		else
			ptr->ymax--;

	}
}
