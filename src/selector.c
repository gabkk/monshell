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
		(*glob)->selector = 1;
	else if (buff[2] == 'B')
		(*glob)->selector = 0;	
}

void				set_selector(t_para **glob, t_input **input, int index, int direction)
{
	t_input 		*ptr;

	ptr = *input;
	while (ptr)
	{
		if (ptr->pos[0] == index)
		{
			if (direction == 1 && ptr->selected == 0)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[32m", (*glob)->fd);
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
			else if (direction == -1 && ptr->selected == 0)
			{
				ft_putchar_fd(' ', (*glob)->fd);
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				ft_putstr_fd("\x1b[32m", (*glob)->fd);
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
	(*glob)->selector = 0;
}


void				selector_paste(t_para **glob, t_input **input)
{
	t_input			*ptr;
	int				j;
	int				position;

	j = 0;
	position = 0;
	if ((*glob)->copy)//(*glob)->copy)
	{
		ptr = (*glob)->copy;//(*glob)->copy;
		position = (*glob)->cursor->posy;
		while (ptr)
		{
			//ft_putchar_fd(ptr->c, (*glob)->fd);
			if (position == (*glob)->total_c)
			{
				add_back_input(input, ptr->c, (*glob)->total_c);
			}
			else
				add_inside_input(input, ptr->c, position);
			//(*glob)->cursor[0]++;
			
			(*glob)->total_c++;
			position++;
			ptr = ptr->next;
		}
		j = (*glob)->cursor->posy;
		while (j > 0)
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			j--;
		}
		j = (*glob)->cursor->posy;// pour le retour apres draw
		(*glob)->cursor->posy = 0;
		ptr = *input;
		while (ptr)
		{
			if (ptr->selected == 1)//faire une fonction
			{
				ft_putstr_fd("\x1b[32m", (*glob)->fd);
				ft_putchar_fd(ptr->c, (*glob)->fd);
				ft_putstr_fd("\x1b[0m", (*glob)->fd);
			}
			else 
				ft_putchar_fd(ptr->c, (*glob)->fd);
			ptr->selected = 0;
			(*glob)->cursor->posy++;
			j++;
			ptr = ptr->next;
		}
		while ((*glob)->cursor->posy > position)
		{
		 	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			(*glob)->cursor->posy--;
		}
		(*glob)->selector = 0;
	}
}