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

void			read_input(t_para *glob, t_input **input, int *index)
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
		ft_putchar_fd(buff[0], glob->fd);
		add_to_lst_input(input, buff[0], *index);
		glob->cursor[0] += 1;
		*index += 1;
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
			if (glob->cursor[0] < *index)
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
	if (buff[0] == '\n')//line
	{
		print_lst_input(input, &glob);
		delete_lst_input(input);
		glob->term->action = 1;
		ft_putchar_fd('\n', glob->fd);
	}
	if (buff[0] == 4)//ctr+d
	{
		exit(0);
	}
}

t_cmd			*read_cmd(t_para *glob)
{
	char		**tmp;
	t_cmd		*base;

	tmp = NULL;
	base = NULL;
	parse_value(&glob, tmp, &base);
	if (glob->term->action == 1)
		add_to_history(glob->cmd);
	free(glob->cmd);
	return (base);
}

void			parse_value(t_para **glob, char **tmp, t_cmd **base)
{
	int			i;
	char		**cmd;

	i = 0;
	if ((checkifonlyspace((*glob)->cmd) == 1))
	{
		(*glob)->term->action = 0;
		print_prompt(*glob);
	}
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
