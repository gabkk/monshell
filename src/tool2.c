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
	ft_putstr_fd("modify ymax last", 2); // debug
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
		ft_putstr_fd("|tmp:", 2);//debug
		ft_putnbr_fd(tmp, 2);//debug
		if (tmp == (*glob)->term->size[0])
		{
			ptr->ymax++;
			ft_putstr_fd("go inside new line", 2);
//			add_cursor(&ptr);
			newm = init_cursor();
			ptr->next = newm;
			newm->prev = ptr;
			newm->posx = ptr->posx + 1;
			newm->next = NULL;
			newm->posy = 1;
			newm->ymax = 0;
			newm->quoting = 0;
		}
		else
			ptr->ymax++;
	}
	else if (value == -1)
	{
//		tmp += ptr->ymax + 1;
		if (ptr->posx > 0 && ptr->ymax == 0)
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

int 				get_input_pos(t_para **glob)
{
	int				position;

	position = 0;
	if ((*glob)->cursor->posx == 0)
		position = (*glob)->cursor->posy;
	else
	{
		position = (*glob)->term->size[0] - (*glob)->prompt_s;//verfier le dernier charactere
		position += (*glob)->cursor->posy;
		position += (((*glob)->cursor->posx - 1) * (*glob)->term->size[0]);//verfier le dernier charactere
	}
	return (position);
}