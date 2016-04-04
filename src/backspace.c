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
	if ((*glob)->cursor->posy - 1 == (*glob)->cursor->ymax)
	{
		if ((*glob)->cursor->quoting == 1 && (*glob)->cursor->ymax == 0)
			return ;
		backspace_last(input, glob);
		if ((*glob)->cursor->posy == 0 && (*glob)->cursor->prev)
		{
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
			(*glob)->cursor->ymax--;
		else
			modify_ymax_to_last(glob, &(*glob)->cursor, -1);
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
		ptr = ptr->next;
	if (ptr->prev)
		ptr->prev->next = NULL;
	unset_quoting(&(*glob)->quoting, ptr->c);
	free(ptr);
	if ((*glob)->cursor->posy == 1 && (*glob)->cursor->posx > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		while (i < (*glob)->term->size[0] + 1) // a voir le - 1
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			i++;
		}
		(*glob)->cursor->posy--;
		ft_putchar_fd(' ', (*glob)->fd);
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
	}
	else
	{
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		ft_putchar_fd(' ', (*glob)->fd);
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);		
	}
	if ((*glob)->cursor->posy == 2 && (*glob)->cursor->posx == 0)
	 	*input = NULL;
}

void				backspace_last_ctrld(t_input **input, t_para **glob)
{
	t_input			*ptr;
	int				i;

	i = 0;
	ptr = *input;
	if (!ptr)
		ft_putstr_fd("input doesn't exist", 2);
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->prev)
		ptr->prev->next = NULL;
	unset_quoting(&(*glob)->quoting, ptr->c);
	free(ptr);
	if ((*glob)->cursor->posy == 1 && (*glob)->cursor->posx > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
		while (i < (*glob)->term->size[0] + 1) // a voir le - 1
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			i++;
		}
		(*glob)->cursor->posy--;
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		ft_putchar_fd(' ', (*glob)->fd);
	}
	else
	{
		ft_putstr_fd("backspacelast ctrld normal", 2);
		ft_putchar_fd(' ', (*glob)->fd);
		ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);		
	}
	if ((*glob)->cursor->posy == 1 && (*glob)->cursor->posx == 0)
	 	*input = NULL;
}

void				backspace_inside(t_input **input, t_para **glob)
{ //creer une fonciton generique pr le ctrl -d
	t_input			*ptr;
	int				x;
	int				y;
	int				position;

	position = get_input_pos(glob);
	back_del_maillon(glob, input, position);
	x = 0;
	ptr = *input;
	while(ptr)
	{
		ptr->pos[0] = x++;
		ptr = ptr->next;
	}
	cursor_pos_init(glob);
	back_redraw(glob, input);
	x = 0;
	y = 0;
	(*glob)->cursor->posy--;
	if ((*glob)->cursor->posy == 0)
	{
		(*glob)->cursor->posy++; //bizar
		(*glob)->cursor = (*glob)->cursor->prev;
		(*glob)->cursor->posy--;
	}
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
}

void				backspace_inside_ctrld(t_input **input, t_para **glob)
{ //creer une fonciton generique pr le ctrl -d et la precedente
	// c est trop code degueulasse serieux .. abuse
	//regler le del du dernier
	//Sinon SEGFAULT
	t_input			*ptr;
	int				i;
	int				x;
	int				y;
	int				position;

	position = get_input_pos(glob) + 1;		
	back_del_maillon(glob, input, position);
	i = 0;
	ptr = *input;
	while(ptr)
	{
		ptr->pos[0] = i++;
		ptr = ptr->next;
	}
	cursor_pos_init(glob);
	back_redraw(glob, input);
	x = 0;
	y = 0;
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
}
