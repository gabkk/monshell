/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cursor_up(t_para **glob)
{
	int		tmp;

	tmp = 0;
	if ((*glob)->cursor->prev)
	{
		if ((*glob)->cursor->prev->posx == 0)
		{
			if ((*glob)->cursor->posy <= (*glob)->prompt_s)
			{
				while ((*glob)->cursor->posy <= (*glob)->prompt_s)
				{
					ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
					(*glob)->cursor->posy++;
				}
				(*glob)->cursor->posy = 1;
				(*glob)->cursor = (*glob)->cursor->prev;
				(*glob)->cursor->posy = 1;
			}
			else
			{
				tmp = (*glob)->cursor->posy;
				(*glob)->cursor->posy = 1;
				(*glob)->cursor = (*glob)->cursor->prev;
				(*glob)->cursor->posy = tmp - (*glob)->prompt_s;
			}
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		}
		else
		{
			tmp = (*glob)->cursor->posy;
			(*glob)->cursor = (*glob)->cursor->prev;
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);	
			(*glob)->cursor->posy = tmp;
		}
	}
}

void		cursor_down(t_para **glob)
{
	int		tmp;

	tmp = 0;
	if ((*glob)->cursor->next)
	{
		if ((*glob)->cursor->posx == 0)
			tmp = (*glob)->cursor->posy + (*glob)->prompt_s;
		else
			tmp = (*glob)->cursor->posy;
		(*glob)->cursor->posy = (*glob)->cursor->ymax + 1;
		(*glob)->cursor = (*glob)->cursor->next;
		if (tmp < (*glob)->cursor->ymax)
			(*glob)->cursor->posy = tmp;
		else
		{
			if ((*glob)->cursor->ymax == 0)
				(*glob)->cursor->posy = 1;
			else
				(*glob)->cursor->posy = (*glob)->cursor->ymax;
			tmp = (*glob)->cursor->ymax;
		}
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);	
		while (tmp > 1)
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			tmp--;
		}
	}
}