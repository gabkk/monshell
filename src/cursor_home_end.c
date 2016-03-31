/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_home_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			cursor_home_end(t_para **glob, t_input **input, char buff)
{
	if (buff == 'H')
		cursor_home(glob, input);
	else if (buff == 'F')
		cursor_end(glob, input);
}

void			cursor_end(t_para **glob, t_input **input)
{//meme fonction que cursor_word_right le signe change
	t_input		*ptr;
	int			position;
	int			tmp;

	tmp = 0;
	ptr = *input;
	position = get_input_pos(glob) - 1;
	while (ptr)
	{
		if (ptr->pos[0] == position)
		{
			break ;
		}
		ptr = ptr->next;
	}
	if (!ptr)
		return ;
	if (ptr->c == '\n' && ptr->next)//a caller
		ptr = ptr->next;
	if((*glob)->cursor->posx == 0)
		tmp = (*glob)->prompt_s;
	tmp += (*glob)->cursor->posy;
	while (ptr)
	{
		if (ptr->c == '\n')
		{
			if (ptr->next)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
				ptr = ptr->next;
			}
			break ;
		}
		else
		{
			if (tmp == (*glob)->term->size[0] && (*glob)->cursor->next)
			{
				ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
				(*glob)->cursor = (*glob)->cursor->next;
				(*glob)->cursor->posy = 0;
				tmp = 0;
			}
			else
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor->posy++;
			tmp++;
		}
		ptr = ptr->next;
	}
}

void			cursor_home(t_para **glob, t_input **input)
{
	int		value;

	value = 0;
	if (!*input)
		return ;
	if ((value = cursor_find_home(glob, input)) == -1)
	{
		cursor_pos_init(glob);
		while ((*glob)->cursor->prev)
			(*glob)->cursor = (*glob)->cursor->prev;
		(*glob)->cursor->posy = 1;
	}
	else
		position_cursor(glob, value);
}

int			cursor_find_home(t_para **glob, t_input **input)
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
	while (ptr)
	{
		if (ptr->c == '\n')
			return (ptr->pos[0] + 1);
		ptr = ptr->prev;
	}
	return (-1);
}
