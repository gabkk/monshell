/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_input_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				backspace(t_input **input, t_para **glob)
{
//	t_cursor		*tmp;

	if ((*glob)->cursor->posy - 1 == (*glob)->cursor->ymax)
	{
		ft_putendl_fd("backspace_last 1", 2);
		backspace_last(input, glob);
		if ((*glob)->cursor->posy == 0 && (*glob)->cursor->prev)
		{
			ft_putstr_fd("move to last cursor", 2);//debug
			(*glob)->cursor = (*glob)->cursor->prev;
			modify_ymax_to_last(glob, &(*glob)->cursor, -1);
			(*glob)->cursor->posy--;
		}
		else
		{
			(*glob)->cursor->posy--;
			(*glob)->cursor->ymax--;
		}

	}
	else if ((*glob)->cursor->posy - 1 < (*glob)->cursor->ymax)
	{
		backspace_inside(input, glob);
		if ((*glob)->cursor->ymax < (*glob)->term->size[0] - (*glob)->prompt_s)
		{
			(*glob)->cursor->ymax--;
			ft_putstr_fd("inferieur", 2);
		}
		else
		{
			ft_putstr_fd("modify last", 2);
			modify_ymax_to_last(glob, &(*glob)->cursor, -1);
		}
	}
	(*glob)->total_c -= 1;

}
void				backspace_last(t_input **input, t_para **glob)
{
	t_input			*ptr;
	int				i;

	i = 0;
	ptr = *input;
	if (!ptr)
		ft_putstr_fd("input doesn't exist", 2);
	while (ptr->next)
	{
		//ft_putchar_fd(ptr->c, 2);
		ptr = ptr->next;
	}
	if (ptr->prev)
		ptr->prev->next = NULL;
	free(ptr);
	if ((*glob)->cursor->posy == 1 && (*glob)->cursor->posx > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		while (i < (*glob)->term->size[0] + 1) // a voir le - 1
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			//ft_putnbr_fd(i, 2);
			i++;
		}
		(*glob)->cursor->posy--;
	}
	else
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	ft_putchar_fd(' ', (*glob)->fd);
	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
	if ((*glob)->cursor->posy == 2 && (*glob)->cursor->posx == 0)
	 	*input = NULL;
}

void				backspace_inside(t_input **input, t_para **glob)
{
	t_input			*ptr;
	int				i;
	int				x;
	int				y;

	back_del_maillon(glob, input);
	x = 0;
	ptr = *input;
	while(ptr)
	{
		ptr->pos[0] = x++;
		ptr = ptr->next;
	}
	back_pos_init(glob);
	back_redraw(glob, input);
	(void)x;
	(void)y;
	x = 0;
	y = 0;
	(*glob)->cursor->posy--;


	if ((*glob)->cursor->posy == 0)
	{
		(*glob)->cursor->posy++; //bizar
//		(*glob)->cursor->ymax = 0;
		(*glob)->cursor = (*glob)->cursor->prev;
		(*glob)->cursor->posy--;
	}


	ft_putendl_fd("", 2);//debug

	ft_putstr_fd("value de y:", 2);//debug
	ft_putnbr_fd((*glob)->cursor->posy, 2);//debug

	ft_putstr_fd("value de x:", 2);//debug
	// ft_putnbr_fd((*glob)->cursor->posx, 2);//debug

	while (x < (*glob)->cursor->posx)
	{
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
		x++;
	}
	while (y + 1 < (*glob)->cursor->posy)
	{
		ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
		y++;
	}

	(void)i;
}
