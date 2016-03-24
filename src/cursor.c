/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cursor		*init_cursor(void)
{
	t_cursor	*newm;

	newm = (t_cursor *)malloc(sizeof(t_cursor));
	newm->posx = 0;
	newm->posy = 1;
	newm->ymax = 0;
	newm->next = NULL;
	newm->prev = NULL;	
	return (newm);
}

void			add_cursor(t_cursor **cursor)
{
	t_cursor	*newm;

	newm = init_cursor();
	(*cursor)->next = newm;
	newm->prev = *cursor;
	newm->posy = 1;
	newm->ymax = 0;
	newm->posx = newm->prev->posx + 1;
	newm->next = NULL;
	*cursor = newm;
}

void			freecursor(t_cursor **cursor)
{
	t_cursor	*tmp;

	while ((*cursor)->prev)
		(*cursor) = (*cursor)->prev;
	while ((*cursor))
	{
		tmp = (*cursor)->next;
		free((*cursor));
		(*cursor) = tmp;
	}
}