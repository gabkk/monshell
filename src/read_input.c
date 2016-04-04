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

void			read_input(t_para *glob, t_input **input)
{
	char		buff[2];
	int  		ret;

	ft_bzero(buff, 2);
	if ((ret = read(0, buff, 1)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	if (ft_isprint(buff[0]) == 1)
	{
		if (glob->selector == 0)
			read_if_print(&glob, input, buff[0]);
		else if (glob->selector == 1)
			selector_action(&glob, input, buff[0]);
	}
	else if (buff[0] == 127)
	{
		if ((glob->cursor->posy > 1) ||
			(glob->cursor->posy > 0 && glob->cursor->posx > 0))
		backspace(input, &glob);
	}
	else if (buff[0] == 27)
		read_arrow(&glob, input);
	else if (buff[0] == '\n' && glob->selector == 0)//line
		read_enter(&glob, input);
	else if (buff[0] == 5)//ctr E
	{
		if (glob->selector == 0)
		{
	//		\033]12;green\007
			ft_putstr_fd(CURSOR_COLOR_B_OS, glob->fd);
			//ft_putstr_fd("\e]12;blue\a", (*glob)->fd);
			glob->selector = 1;
		}
		else if (glob->selector == 1)
		{
			ft_putstr_fd(CURSOR_COLOR_W_OS, glob->fd);
			//ft_putstr_fd("\e]12;white\a", (*glob)->fd);
			glob->selector = 0;	
		}
	}
	else if (buff[0] == 4)//ctr+d
	{
		ft_putstr_fd("TOTAL : " ,2);// debug
		ft_putnbr_fd(glob->total_c ,2);
		ft_putstr_fd("pos : " ,2);
		ft_putnbr_fd(get_input_pos(&glob) ,2);// debug
		
		// modifier le bug pos-- quand on ctrl-d au milieur
		// revoir les fonction backspace_inside_ctrld et backspace_last_ctrld
		// revoir ces if bizarre en dessous


		int			pos;

		if (!*input)
			return ;
		pos = 0 ;
		pos = getpos_from_input(input);
		if (pos < glob->total_c)
		{
			backspace_inside_ctrld(input, &glob);
			if (glob->cursor->ymax < glob->term->size[0] - glob->prompt_s)
				glob->cursor->ymax--;
			else
				modify_ymax_to_last(&glob, &glob->cursor, -1);
			glob->total_c -= 1;
		}
		else if (pos == glob->total_c)
		{
			backspace_last_ctrld(input, &glob);
			if (glob->cursor->posy == 0 && glob->cursor->prev)
			{
				glob->cursor = glob->cursor->prev;
				modify_ymax_to_last(&glob, &glob->cursor, -1);
			}
			else
				glob->cursor->ymax--;
			glob->total_c -= 1;
		}
		else if (pos > glob->total_c &&
			glob->cursor->posy == 1)
		{
			ft_putstr_fd(CURSOR_COLOR_W_OS, glob->fd);
			exit(0);
		}
	}

//	me
}

void		read_enter(t_para **glob, t_input **input)
{
	if (quoting_valid((*glob)->quoting) == 0)
	{
		(*glob)->quoting->bkslash = 0;
		add_cursor(&(*glob)->cursor);
		ft_putchar_fd('\n', (*glob)->fd);
		ft_putstr_fd("\033[34m\\\033[0m ", (*glob)->fd);
		(*glob)->cursor->quoting = 1;
		(*glob)->term->action = 0;
		return ;
	}
	save_cmd(input, glob);
	if (*input)
		delete_lst_input(input);
	while ((*glob)->cursor->next)
	{
		(*glob)->cursor = (*glob)->cursor->next;
		if ((*glob)->cursor->ymax > 0)
			ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
	}
}

void		read_arrow(t_para **glob, t_input **input)
{
	char	buff[2];
	int		ret;

	ft_bzero(buff, 2);
	if ((ret = read(0, buff, 2)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	
	if ((buff[1] == 'A' || buff[1] == 'B') &&
		(((*glob)->cursor->posy == 0 || (*glob)->current_h - 1 <= (*glob)->total_h)) &&
		(*glob)->selector == 0)
	{
		read_ud(glob, input, buff[1]);	
	}
	else if (buff[1] == 'C' || buff[1] == 'D')
		read_lr(glob, input, buff[1]);
	else if (buff[1] == '1')
		mode_selector(glob, input);
	else if ((buff[0] == 'O' || buff[0] == '\[') &&
		(buff[1] == 'H' || buff[1] == 'F'))
	{
		cursor_home_end(glob, input, buff[1]);
	}
}

void		read_ud(t_para **glob, t_input **input, char buff)
{
	clear_line(glob, input);
	if ((*glob)->cursor) // a verifier
		freecursor(&(*glob)->cursor);
	(*glob)->cursor = init_cursor();
	if (*input)
		delete_lst_input(input);
	if (buff == 'A' && (*glob)->current_h - 1 > 0)
		(*glob)->current_h--;
	else if (buff == 'B' && (*glob)->current_h < (*glob)->total_h)
		(*glob)->current_h++;
	show_last_hist(glob, input);

}

void		read_lr(t_para **glob, t_input **input, char buff)
{
	int		i;

	i = 0;
	if (buff == 'C')//droite
	{
		if ((*glob)->cursor->posy < (*glob)->cursor->ymax + 1)
		{
			if ((*glob)->selector == 1)
				set_selector(glob, input, 1);
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor->posy += 1;
		}
		if ((*glob)->cursor->next)
		{
			if ((*glob)->cursor->posy == (*glob)->cursor->ymax + 1)
			{
				ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
				(*glob)->cursor = (*glob)->cursor->next;				
			}
		}

		ft_putchar_fd('\n', 2); // debug
		ft_putstr_fd("|posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);
		ft_putstr_fd("|prompt:", 2);
		ft_putnbr_fd((*glob)->prompt_s, 2);
		ft_putstr_fd("|posy:", 2);
		ft_putnbr_fd((*glob)->cursor->posy, 2);
		ft_putstr_fd("|ymax:", 2);
		ft_putnbr_fd((*glob)->cursor->ymax, 2); // debug
	}
	else if (buff == 'D')//gauche
	{
		if ((*glob)->cursor->posy > 1) // bug viens de la
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			if ((*glob)->selector == 1)
				set_selector(glob, input, -1);
			(*glob)->cursor->posy -= 1;
		}
		else if ((*glob)->cursor->prev && (*glob)->cursor->posy == 1 && (*glob)->cursor->quoting == 0)
		{
			ft_putstr_fd(tgetstr("up", NULL),(*glob)->fd);
			i = (*glob)->term->size[0] - (*glob)->cursor->posy ;
			i++;
			while (i > 0)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				i--;
			}
			if ((*glob)->selector == 1)
				set_selector(glob, input, -1);
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor = (*glob)->cursor->prev;
			(*glob)->cursor->posy = (*glob)->cursor->ymax;
		}


		ft_putchar_fd('\n', 2);//debug
		ft_putstr_fd("|posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2); // debug
		ft_putstr_fd("|prompt:", 2);
		ft_putnbr_fd((*glob)->prompt_s, 2);
		ft_putstr_fd("|posy:", 2);
		ft_putnbr_fd((*glob)->cursor->posy, 2); // debug
		ft_putstr_fd("|ymax:", 2);
		ft_putnbr_fd((*glob)->cursor->ymax, 2); // debug
	}
}

void		read_if_print(t_para **glob, t_input **input, char buff)
{
	int		position;

	position = 0;
	set_quoting(&(*glob)->quoting, buff);
	if ((*glob)->cursor->posy == (*glob)->cursor->ymax + 1 &&
		(*glob)->cursor->posy < (*glob)->term->size[0] + 1)
	{
		add_back_input(input, buff, (*glob)->total_c);
		ft_putchar_fd(buff, (*glob)->fd);
		(*glob)->total_c += 1;
		if ((*glob)->cursor->ymax < (*glob)->term->size[0])
		{
			(*glob)->cursor->ymax += 1;
			(*glob)->cursor->posy += 1;			
		}
		ft_putchar_fd('b', 2); // debug
		ft_putnbr_fd((*glob)->total_c, 2); // debug

	}
	else if ((*glob)->cursor->posy < (*glob)->cursor->ymax + 1 || (*glob)->cursor->posy == 1)
	{
		int tmp;//woouuu
		t_cursor		*newm;

		if ((*glob)->cursor->posx == 0)
			tmp = (*glob)->term->size[0] - (*glob)->prompt_s;
		else
			tmp = (*glob)->term->size[0];
		position = get_input_pos(glob);
		add_inside_input(input, buff, position);
		(*glob)->cursor->posy += 1;//y final
		ft_putendl_fd("", 2); // debug
		if ((*glob)->cursor->ymax < tmp)
		{
			ft_putstr_fd("modify ymax inside", 2); // debug
			(*glob)->cursor->ymax++;
			if ((*glob)->cursor->ymax == tmp)
			{
				newm = init_cursor();
				(*glob)->cursor->next = newm;
				newm->prev = (*glob)->cursor;
				newm->posx = (*glob)->cursor->posx + 1;
				newm->next = NULL;
				newm->posy = 1;
				newm->ymax = 0;
				newm->quoting = 0;
			}
		}
		else
		{
			modify_ymax_to_last(glob, &(*glob)->cursor, 1);
		}

		(*glob)->total_c += 1;

		// ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
		print_lst_input(input, glob); //changer le posy et le posx
	}

	if ((*glob)->cursor->posx == 0 && 
		(((*glob)->cursor->posy + (*glob)->prompt_s) > (*glob)->term->size[0]))
	{
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
		if (!(*glob)->cursor->next)
			add_cursor(&(*glob)->cursor);
		else
			(*glob)->cursor = (*glob)->cursor->next;
	}
	else if ((*glob)->cursor->posx > 0 &&
		((*glob)->cursor->posy > (*glob)->term->size[0]))
	{
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
		if (!(*glob)->cursor->next)
			add_cursor(&(*glob)->cursor);
		else
			(*glob)->cursor = (*glob)->cursor->next;
	}
	else if ((*glob)->cursor->quoting == 1 &&
				(*glob)->cursor->posx > 0 &&
					((*glob)->cursor->posy > (*glob)->term->size[0] - 2))
	{
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
		if (!(*glob)->cursor->next)
			add_cursor(&(*glob)->cursor);
		else
			(*glob)->cursor = (*glob)->cursor->next;
	}
}
