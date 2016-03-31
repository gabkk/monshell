/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cursor_word_left(t_para **glob, t_input **input)
{
	int		value;

	value = 0;
	if (!*input)
		return ;
	if ((value = cursor_find_left(glob, input)) == -1)
	{
		cursor_pos_init(glob);
		while ((*glob)->cursor->prev)
			(*glob)->cursor = (*glob)->cursor->prev;
		(*glob)->cursor->posy = 1;
	}
	else
		position_cursor(glob, value);
}

int			cursor_find_left(t_para **glob, t_input **input)
{
	t_input		*ptr;
	int			position;

	ptr = *input;
	position = get_input_pos(glob) - 1;
	while (ptr)
	{
		if (ptr->pos[0] == position - 1)
			break ;
		ptr = ptr->next;
	}
	if (ptr)
	{
		if (ptr->c == ' ')
		{
			while (ptr->prev && ptr->c == ' ')
				ptr = ptr->prev;
		}
		if (ptr->c != ' ' && ptr->c != '\n')
		{
			while (ptr->prev && ptr->prev->c != ' ' && ptr->prev->c !='\n')
				ptr = ptr->prev;
		}
		return (ptr->pos[0] + 1);
	}
	return (-1);
}

void		cursor_word_right(t_para **glob, t_input **input)
{
	t_input		*ptr;
	int			position;
	int			final;

	ptr = *input;
	position = get_input_pos(glob) - 1;
	if (position == (*glob)->total_c)
	{
		ft_putstr_fd("sortit",2);//debug
		return ;
	}
	final = position;
	while (ptr)
	{
		if (ptr->pos[0] > position)
		{
			if (ptr->c != ' ')
			{
				while (ptr->next && ptr->c != ' ')
				{
					if (ptr->c == ' ')
						break ;
					ptr = ptr->next;
				}
			}
			if (ptr->c == ' ')
			{
				while (ptr->next && ptr->c == ' ')
				{
					if (ptr->c != ' ')
						break ;
					ptr = ptr->next;
				}
			}
			final = ptr->pos[0];
			break ;		
		}
		ptr = ptr->next;
	}
	if (!ptr->next)
	{
		final++;
	}
	if (position != final)
		cursor_find_right(glob, position , final);
}

void			cursor_find_right(t_para **glob, int position, int final)
{
	int y;

	y = 0;
	if ((*glob)->cursor->posx == 0)
		y = (*glob)->prompt_s;
	y += (*glob)->cursor->posy;
	while (position < final)
	{
		y++;
		(*glob)->cursor->posy++;
		ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
		if (y > (*glob)->term->size[0] && (*glob)->cursor->next)
		{
			(*glob)->cursor->posy--;
			ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
			(*glob)->cursor = (*glob)->cursor->next;
			y = 1;
		}
		position++;
	}
}
