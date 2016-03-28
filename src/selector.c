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

void				mode_selector(t_para **glob, t_input **input)
{
	char			buff[3];
	int  			ret;

	ft_bzero(buff, 3);
	if ((ret = read(0, buff, 3)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	if (buff[1] == '2' && buff[2] == 'A')
	{
		ft_putstr_fd("\e]12;blue\a", (*glob)->fd);
		(*glob)->selector = 1;
	}
	else if (buff[1] == '2' && buff[2] == 'B')
	{
		ft_putstr_fd("\e]12;white\a", (*glob)->fd);
		(*glob)->selector = 0;	
	}
	else if (buff[1] == '5' && buff[2] == 'A')
	{
		cursor_up(glob);
	}
	else if (buff[1] == '5' && buff[2] == 'B')
	{
		cursor_down(glob);
	}
	else if (buff[1] == '5' && buff[2] == 'D')//gauche
	{
		cursor_word_left(glob, input);
	}
	else if (buff[1] == '5' && buff[2] == 'C')//droite
	{
		cursor_word_right(glob, input);
	}
}

void				set_selector(t_para **glob, t_input **input, int direction)
{
	t_input 		*ptr;
	int 			position;


	position = get_input_pos(glob) - 1;
	ptr = *input;
	while (ptr)
	{
		ft_putstr_fd("position", 2);
		ft_putnbr_fd(position, 2);
		if (ptr->pos[0] == position)
		{
			if (direction == 1 && ptr->selected == 0)
			{
				// ft_putchar_fd(' ', (*glob)->fd);
				// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[34m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 1;
			}
			else if (direction == 1 && ptr->selected == 1)
			{
				// ft_putchar_fd(' ', (*glob)->fd);
				// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 0;
			}
		}
		else if (ptr->pos[0] == position - 1)
		{
			if (direction == -1 && ptr->selected == 0)
			{
				// ft_putchar_fd(' ', (*glob)->fd);
				// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[34m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 1;
			}
			else if (direction == -1 && ptr->selected == 1)
			{
				// ft_putchar_fd(' ', (*glob)->fd);
				// ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 0;
			}
		}
		ptr = ptr->next;
	}
}

void				selector_action(t_para **glob, t_input **input, int buff)
{
	if (buff == 'c')
		selector_copy(glob, input);
	else if (buff == 'x') // utiliser copier
		selector_cut(glob, input);
	else if (buff == 'v')
		selector_paste(glob, input);
}

void				selector_copy(t_para **glob, t_input **input)
{
	t_input			*ptr;
	int				i;

	i = 0;
	ptr = *input;
	if (&(*glob)->copy)
		delete_lst_input(&(*glob)->copy);
	while (ptr)
	{
		if (ptr->selected == 1)
		{
			add_back_input(&(*glob)->copy, ptr->c, i);
			i++;
		}
		ptr = ptr->next;
	}
	ft_putstr_fd("\e]12;white\a", (*glob)->fd);
	(*glob)->selector = 0;
}


void				selector_cut(t_para **glob, t_input **input)
{
	t_input			*ptr;
	t_input			*tmp;
	int					x;
	int					y;
	int					final;

	x = 0;
	y = 0;
	ptr = *input;
	tmp = ptr;
	if (!ptr)
		return ;
	if (&(*glob)->copy)
		delete_lst_input(&(*glob)->copy);

	cursor_pos_init(glob);

	y = (*glob)->prompt_s;
	x = 0;
	while (tmp)
	{
 	 	ft_putchar_fd(' ', (*glob)->fd);
 	 	y++;
 	 	if (y > (*glob)->term->size[0])
 	 	{
 	 		x++;
 	 		y = 1;
 	 	}
		tmp = tmp->next;
	}
	(*glob)->cursor->posx = x;
	if ((*glob)->cursor->posx == 0)
		y -= (*glob)->prompt_s;

	(*glob)->cursor->posy = y + 1;
	cursor_pos_init(glob);
	final = free_input_copy_buff(glob,input);

	if (&(*glob)->cursor)
		freecursor(&(*glob)->cursor);
	(*glob)->cursor = init_cursor();
	(*glob)->cursor->posy = 1;

	redraw_input(glob, input);

	final++;
	position_cursor(glob, final);

	ft_putstr_fd("\e]12;white\a", (*glob)->fd);
	(*glob)->selector = 0;
}


void				selector_paste(t_para **glob, t_input **input)
{
	int				position;
	int				final;

	position = get_input_pos(glob);
	final = position;
	if ((*glob)->copy)//(*glob)->copy)
	{
		if ((final = save_copy(glob, input)) == -1) //exit
		{
			ft_putstr_fd("\e]12;white\a", (*glob)->fd);
			(*glob)->selector = 0;
			return ; //definir le type d exit
		}
		//reset
		cursor_pos_init(glob);
		if (&(*glob)->cursor)
			freecursor(&(*glob)->cursor);
		(*glob)->cursor = init_cursor();
		(*glob)->cursor->posy = 1;
		// le add inside continue et a la pos final
		redraw_input(glob, input);
		position_cursor(glob, final);
	}
	ft_putstr_fd("\e]12;white\a", (*glob)->fd);
	(*glob)->selector = 0;
	return ; //definir le type d exit
}