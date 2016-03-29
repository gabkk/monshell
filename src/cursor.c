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
	newm->quoting = 0;
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
	newm->quoting = 0;
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

void		cursor_pos_init(t_para **glob)
{
	int				x;
	int				y;
	int				prompt;
	

	y = (*glob)->cursor->posy;
	x = (*glob)->cursor->posx;
	prompt = (*glob)->prompt_s;
	if (x > 0)//fonction dupplique
	{
		ft_putendl_fd("curpos_init x>0", 2);//debug

		while (x > 0)
		{
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
			x--;
		}
		if (y < prompt)
		{	
			while (y < prompt + 1)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				y++;
			}
		}
		else if (y > prompt)
		{	
			while (y > prompt + 1)
			{
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				y--;
			}
		}
		else
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
	}
	else
	{
		ft_putendl_fd("curpos_init esle", 2);//debug
		while (y > 1)
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			y--;
		}		
	}
}