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
	char	buff[2];
	int  ret;

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
		if (glob->cursor->posy > 1)
			backspace(input, &glob);
		else if (glob->cursor->posy > 0 && glob->cursor->posx > 0)
			backspace(input, &glob);
	}
	else if (buff[0] == 27)
		read_arrow(&glob, input);
	else if (buff[0] == '\n')//line
	{
		save_cmd(input, &glob);
		if (*input)
			delete_lst_input(input);
	}
	else if (buff[0] == 4)//ctr+d
		exit(0);
}

void		read_arrow(t_para **glob, t_input **input)
{
	char	buff[2];
	int  ret;

	ft_bzero(buff, 2);
	if ((ret = read(0, buff, 2)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	
	if ((buff[1] == 'A' || buff[1] == 'B') &&
		(((*glob)->cursor->posy == 0 || (*glob)->current_h - 1 <= (*glob)->total_h)))
	{
		read_ud(glob, input, buff[1]);	
	}
	else if (buff[1] == 'C' || buff[1] == 'D')
		read_lr(glob, input, buff[1]);
	else if (buff[1] == '1')
		mode_selector(glob);
}

void		read_ud(t_para **glob, t_input **input, char buff)
{
	clear_line(glob, input);
	if (&(*glob)->cursor)
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
		//ft_putstr_fd("|posy:", 2);
		//ft_putnbr_fd((*glob)->cursor->posy, 2);
		if ((*glob)->cursor->posy < (*glob)->cursor->ymax + 1)
		{
			if ((*glob)->selector == 1)
				set_selector(glob, input, (*glob)->cursor->posy, 1);
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

		

		ft_putchar_fd('\n', 2);
		ft_putstr_fd("|posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);
		ft_putstr_fd("|prompt:", 2);
		ft_putnbr_fd((*glob)->prompt_s, 2);
		ft_putstr_fd("|posy:", 2);
		ft_putnbr_fd((*glob)->cursor->posy, 2);
		ft_putstr_fd("|ymax:", 2);
		ft_putnbr_fd((*glob)->cursor->ymax, 2);
	}
	else if (buff == 'D')//gauche
	{
		if ((*glob)->cursor->posy > 1)
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			if ((*glob)->selector == 1)
				set_selector(glob, input, (*glob)->cursor->posy - 1, -1);
			(*glob)->cursor->posy -= 1;
		}
		else if ((*glob)->cursor->prev && (*glob)->cursor->posy == 1)
		{
			ft_putstr_fd(tgetstr("up", NULL),(*glob)->fd);
			i = (*glob)->term->size[0] - (*glob)->cursor->posy;
			while (i > 0)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				i--;
			}
			(*glob)->cursor = (*glob)->cursor->prev;
			(*glob)->cursor->posy -= 1;
		}


		ft_putchar_fd('\n', 2);
		ft_putstr_fd("|posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);
		ft_putstr_fd("|prompt:", 2);
		ft_putnbr_fd((*glob)->prompt_s, 2);
		ft_putstr_fd("|posy:", 2);
		ft_putnbr_fd((*glob)->cursor->posy, 2);
		ft_putstr_fd("|ymax:", 2);
		ft_putnbr_fd((*glob)->cursor->ymax, 2);
	}
}

void		read_if_print(t_para **glob, t_input **input, char buff)
{
	int		position;

	position = 0;
	if ((*glob)->cursor->posy == (*glob)->cursor->ymax + 1)
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
		if ((*glob)->cursor->posx == 0)
			position = (*glob)->cursor->posy;
		else
		{
			position = (*glob)->term->size[0] - (*glob)->prompt_s;//verfier le dernier charactere
			position += (*glob)->cursor->posy;
			position += (((*glob)->cursor->posx - 1) * (*glob)->term->size[0]);//verfier le dernier charactere
		}
		add_inside_input(input, buff, position);

		(*glob)->cursor->posy += 1;//y final


		if ((*glob)->cursor->ymax < (*glob)->term->size[0] - (*glob)->prompt_s)
		{
			(*glob)->cursor->ymax++;
			ft_putstr_fd("inferieur", 2);
		}
		else
		{
			ft_putstr_fd("modify last", 2);
			// if (!(*glob)->cursor->next)
			// 	add_cursor(&(*glob)->cursor);
			modify_ymax_to_last(glob, &(*glob)->cursor, 1);
		}


//		(*glob)->cursor->ymax += 1;



		(*glob)->total_c += 1;
		// ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
		print_lst_input(input, glob); //changer le posy et le posx


		ft_putchar_fd('i', 2); // debug
		ft_putnbr_fd(position, 2); // debug

	}

	if ((*glob)->cursor->posx == 0 && 
		(((*glob)->cursor->posy + (*glob)->prompt_s) > (*glob)->term->size[0]))
	{
		ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
		if (!(*glob)->cursor->next)
			add_cursor(&(*glob)->cursor);
		else
			(*glob)->cursor = (*glob)->cursor->next;
		// ft_putchar_fd('\n', 2);
		// ft_putstr_fd("|posx:", 2);
		// ft_putnbr_fd((*glob)->cursor->posx, 2);
		// ft_putstr_fd("|prompt:", 2);
		// ft_putnbr_fd((*glob)->prompt_s, 2);
		// ft_putstr_fd("|posy:", 2);
		// ft_putnbr_fd((*glob)->cursor->posy, 2);
		// ft_putstr_fd("|ymax:", 2);
		// ft_putnbr_fd((*glob)->cursor->ymax, 2);
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
	// else if ((*glob)->cursor->next)
	// {
	// 	ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
	// 	(*glob)->cursor = (*glob)->cursor->next;	
	// }
}
			