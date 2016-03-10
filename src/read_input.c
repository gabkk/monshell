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

void			read_input(t_para *glob, t_input **input, int index)
{
	char	buff[2];
	int  ret;

	ft_bzero(buff, 2);
	if ((ret = read(0, buff, 1)) == 0)
		exit(0);
	if (ret == -1)
		ft_putendl_fd("read error", 2);
	if ((buff[0]))
	{
		ft_putchar_fd(buff[0], glob->fd);
		add_to_lst_input(input, buff[0], index);
		(*input)->index++;
	}
	else if (buff[0] == 27)
	{
		if (buff[0] == 27)
		{
			ft_putendl_fd("F", glob->fd);
		}
		ft_bzero(buff, 2);
		return ;
	}
	if (buff[0] == '\n')//line
	{
		print_lst_input(input, &glob);
		delete_lst_input(input);
		glob->term->action = 1;
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
