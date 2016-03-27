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

void				mode_selector(t_para **glob)
{
	char			buff[3];
	int  			ret;

	ft_bzero(buff, 3);
	if ((ret = read(0, buff, 3)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	if (buff[2] == 'A')
	{
		ft_putstr_fd("\e]12;blue\a", (*glob)->fd);
		(*glob)->selector = 1;
	}
	else if (buff[2] == 'B')
	{
		ft_putstr_fd("\e]12;white\a", (*glob)->fd);
		(*glob)->selector = 0;	
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
		if (ptr->pos[0] == position)
		{
			if (direction == 1 && ptr->selected == 0)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[34m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 1;
			}
			else if (direction == 1 && ptr->selected == 1)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 0;
			}
		}
		else if (ptr->pos[0] == position - 1)
		{
			if (direction == -1 && ptr->selected == 0)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[34m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ptr->selected = 1;
			}
			else if (direction == -1 && ptr->selected == 1)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
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
	int				i;
	int				j;
	int				position_f;
	int				longueur;

	j = 0;
	position_f = -1;
	longueur = 0;
	i = 0;
	ptr = *input;
	if (!ptr)
		return ;
	if (&(*glob)->copy)
		delete_lst_input(&(*glob)->copy);
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
			(*glob)->cursor->ymax--;
			i++;
		}
		else
			ptr = ptr->next;
	}
	j = (*glob)->cursor->posy;// pour le retour apres draw
	while (j > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		j--;
	}
	ptr = *input;
	longueur = i;// pour le retour apres draw
	(*glob)->cursor->posy = 0;
	while (ptr)
	{
		ft_putchar_fd(ptr->c, (*glob)->fd);
		ptr->pos[0] = (*glob)->cursor->posy;
		(*glob)->cursor->posy++;
//			j++;
		ptr = ptr->next;
	}
	while (longueur > 0)
	{
	 	ft_putchar_fd(' ', (*glob)->fd);
		longueur--;
	}
	longueur = i;
	//while (longueur > 0)
	while (longueur > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		(*glob)->total_c--;
		longueur--;
	}
	//(*glob)->total_c++;
	while ((*glob)->cursor->posy - 1 > position_f)
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		(*glob)->cursor->posy--;	
	}

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
		cursor_pos_init(glob);
		//reset
		if (&(*glob)->cursor)
			freecursor(&(*glob)->cursor);
		(*glob)->cursor = init_cursor();
		(*glob)->cursor->posy = 1;


		// le add inside continue et a la pos final
		redraw_with_copy(glob, input);

		ft_putendl_fd("\n", 2);//debug
		ft_putstr_fd("|final:", 2);
		ft_putnbr_fd(final, 2);
		ft_putstr_fd("|total:", 2);
		ft_putnbr_fd((*glob)->total_c, 2);//debug

		int xfinal;
		int tmp;
		int yfinal;

		tmp = final;
		xfinal = 0;
		yfinal = (*glob)->prompt_s;
		while (tmp > 0)
		{
			yfinal++;
			if (yfinal > (*glob)->term->size[0])
			{
				xfinal++;
				yfinal = 1;
			}
			tmp--;
		}

		ft_putchar_fd('\n', 2);//debug
		ft_putstr_fd("|xfinal:", 2);
		ft_putnbr_fd(xfinal, 2);
		ft_putstr_fd("|yfinal:", 2);
		ft_putnbr_fd(yfinal, 2);//debug


	if ((*glob)->cursor->posx > xfinal)// dans le cas sup a zero
	{
		if ((*glob)->cursor->posy < yfinal)
		{
			while ((*glob)->cursor->posy < yfinal)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
			}
		}
		else if ((*glob)->cursor->posy > yfinal)
		{
			while ((*glob)->cursor->posy > yfinal)
			{
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				(*glob)->cursor->posy--;
			}
		}
		while ((*glob)->cursor->posx > xfinal)// dans le cas sup a zero
		{
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
			if ((*glob)->cursor->prev)
			{
				(*glob)->cursor->posy = 1;
				(*glob)->cursor = (*glob)->cursor->prev;
			}
		}
		if ((*glob)->cursor->posx == 0)
			yfinal -= (*glob)->prompt_s;
		(*glob)->cursor->posy = yfinal;
	}
	else
	{
		if ((*glob)->cursor->posx == 0)
			yfinal -= (*glob)->prompt_s;
		if ((*glob)->cursor->posy < yfinal)
		{
			while ((*glob)->cursor->posy < yfinal)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
			}
		}
		else if ((*glob)->cursor->posy > yfinal)
		{
			while ((*glob)->cursor->posy > yfinal)
			{
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				(*glob)->cursor->posy--;
			}
		}
	}

		ft_putstr_fd("\e]12;white\a", (*glob)->fd);
		(*glob)->selector = 0;
	}
}