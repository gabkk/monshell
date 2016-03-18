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

void			read_input(t_para *glob, t_input **input, int *total)
{
	char	buff[1];
	int  ret;

	ft_bzero(buff, 1);
	if ((ret = read(0, buff, 1)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	if (ft_isprint(buff[0]) == 1)
		read_if_print(&glob, input, total, buff[0]);
	else if (buff[0] == 127)
	{
		if (glob->cursor[0] > 0)
			backspace(input, &glob, total);	
	}
	else if (buff[0] == 27)
		read_arrow(&glob, input, total);
	else if (buff[0] == '^')
	{
		// if (buff[1] == 'X')
		// 	ft_putchar_fd('&', glob->fd);
	}
	else if (buff[0] == '\n')//line
		save_cmd(input, &glob);
	if (buff[0] == 4)//ctr+d
		exit(0);
}

void		read_arrow(t_para **glob, t_input **input, int *total)
{
	char	buff[2];
	int  ret;

	ft_bzero(buff, 2);
	if ((ret = read(0, buff, 2)) == 0)
		exit(0);
	else if (ret == -1)
		exit(EXIT_FAILURE);
	
	if ((buff[1] == 'A' || buff[1] == 'B') &&
		(((*glob)->cursor[0] == 0 || (*glob)->current_h - 1 <= (*glob)->total_h)))
	{
		read_ud(glob, input, buff[1], total);	
	}
	else if (buff[1] == 'C' || buff[1] == 'D')
		read_lr(glob, buff[1], total);
}
void		read_ud(t_para **glob, t_input **input, char buff, int *total)
{
	clear_line(*glob, input);
	if (*input)
		delete_lst_input(input);
	if (buff == 'A' && (*glob)->current_h - 1 > 0)
		(*glob)->current_h--;
	else if (buff == 'B' && (*glob)->current_h < (*glob)->total_h)
		(*glob)->current_h++;
	show_last_hist(glob, input, total);

}
void		read_lr(t_para **glob, char buff, int *total)
{
	if (buff == 'C')//droite
	{
		if ((*glob)->cursor[0] < *total)
		{
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor[0] += 1;
		}
	}
	else if (buff == 'D')//gauche
	{
		if ((*glob)->cursor[0] > 0)
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			(*glob)->cursor[0] -= 1;
		}
	}
}

void		read_if_print(t_para **glob, t_input **input, int *total, char buff)
{
	if ((*glob)->cursor[0] == *total)
	{
		add_back_input(input, buff, *total);
		ft_putchar_fd(buff, (*glob)->fd);
	}
	else if ((*glob)->cursor[0] < *total || (*glob)->cursor[0] == 0)
	{
		add_inside_input(input, buff, (*glob)->cursor[0]);
		print_lst_input(input, glob);
	}
	(*glob)->cursor[0] += 1;
	*total += 1;
}
			