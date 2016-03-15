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
	char	buff[3];
	int  ret;

	ft_bzero(buff, 3);
	if ((ret = read(0, buff, 3)) == 0)
		exit(0);
	if (ret == -1)
	{
		ft_putendl_fd("read error", 2);
		exit(0);
	}
	if (ft_isprint(buff[0]) == 1)
	{
		if (glob->cursor[0] == *total)
		{
			add_back_input(input, buff[0], *total);
			ft_putchar_fd(buff[0], glob->fd);
		}
		else if (glob->cursor[0] < *total || glob->cursor[0] == 0)
		{
			add_inside_input(input, buff[0], glob->cursor[0]);
			print_lst_input(input, &glob);
		}
		glob->cursor[0] += 1;
		*total += 1;
		ft_bzero(buff, 3);
	}
	else if (buff[0] == 127 || (buff[0] == 27 && buff[2] == '3'))
	{
		if (buff[0] == 127 && glob->cursor[0] > 0)
		{
			backspace(input, &glob, total);
//			print_lst_input(input, &glob);
			// ft_putchar_fd(' ', (*glob)->fd);

			*total -= 1;
		}
		ft_bzero(buff, 3);
	}
	else if (buff[0] == 27)
	{
		if (buff[2] == 'A')
			ft_putstr_fd("up", glob->fd);
		else if (buff[2] == 'B')
			ft_putstr_fd("down", glob->fd);
		else if (buff[2] == 'C')//droite
		{
			if (glob->cursor[0] < *total)
			{
				ft_putstr_fd(tgetstr("nd", NULL), glob->fd);
				glob->cursor[0] += 1;
			}
		}
		else if (buff[2] == 'D')//gauche
		{
			if (glob->cursor[0] > 0)
			{
				ft_putstr_fd(tgetstr("le", NULL), glob->fd);
				glob->cursor[0] -= 1;				
			}
		}
		ft_bzero(buff, 3);
		return ;
	}
	else if (buff[0] == '\n')//line
	{
		save_cmd(input, &glob);
		delete_lst_input(input);
		glob->term->action = 1;
		ft_putchar_fd('\n', glob->fd);
	}
	if (buff[0] == 4)//ctr+d
		exit(0);
}

void			parse_value(t_para **glob, t_cmd **base)
{
	int			i;
	char		**cmd;
	char		**tmp;

	i = 0;
	tmp = NULL;
	if ((checkifonlyspace((*glob)->cmd) == 1))
		(*glob)->term->action = 0;
	else
	{
		cmd = ft_strsplit((*glob)->cmd, ';');
		if (!*cmd)
			return ;
		while (cmd[i])
		{
			tmp = parse_cmd(cmd[i]);
			if (tmp)
				add_maillon_cmd(tmp, base);
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}
