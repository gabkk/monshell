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
		if (glob->cursor[0] > 0)
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
		(((*glob)->cursor[0] == 0 || (*glob)->current_h - 1 <= (*glob)->total_h)))
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
	clear_line(*glob, input);
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
	if (buff == 'C')//droite
	{
		if ((*glob)->cursor[0] < (*glob)->total_c)
		{
			if ((*glob)->selector == 1)
				set_selector(glob, input, (*glob)->cursor[0], 1);
			ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
			(*glob)->cursor[0] += 1;
		}
	}
	else if (buff == 'D')//gauche
	{
		if ((*glob)->cursor[0] > 0)
		{
			ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
			if ((*glob)->selector == 1)
				set_selector(glob, input, (*glob)->cursor[0] - 1, -1);
			(*glob)->cursor[0] -= 1;
		}
	}
}

void		read_if_print(t_para **glob, t_input **input, char buff)
{
	if ((*glob)->cursor[0] == (*glob)->total_c)
	{
		add_back_input(input, buff, (*glob)->total_c);
		ft_putchar_fd(buff, (*glob)->fd);
	}
	else if ((*glob)->cursor[0] < (*glob)->total_c || (*glob)->cursor[0] == 0)
	{
		add_inside_input(input, buff, (*glob)->cursor[0]);
		print_lst_input(input, glob);
	}
	(*glob)->cursor[0] += 1;
	(*glob)->total_c += 1;
}
			