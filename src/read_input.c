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
	char	buff[4];
	int		index;

	index = 0;
	read(glob->fd, buff, 4);
	if (buff[0] != '\n' && ft_isprint(buff[0]))
	{
		ft_putchar_fd(buff[0], glob->fd);
		add_to_lst_input(input, buff[0], index);
	}
	else if (buff[0] == 27)
	{
		if (buff[0] == 27)
		{
			//key-arrow
			ft_putendl_fd("F", glob->fd);
			//exit(0);			
		}
		else if (buff[0] == 127 || (buff[0] == 27 && buff[2] == '3'))//del
			ft_putendl_fd("delete", glob->fd);
		ft_bzero(buff, 4);
		return ;
	}
	else if (buff[0] == '\n')//line
	{

		ft_putendl_fd(" ", glob->fd);
		print_lst_input(input, &glob);
		//delete free la liste input
		delete_lst_input(input);
		glob->term->action = 1;
	}
	ft_bzero(buff, 4);
}

void			read_cmd(t_para *glob, t_cmd **base)
{
	char		**tmp;

	tmp = NULL;
	if (glob->cmd)
	{
		add_to_history(glob->cmd);
		parse_value(&glob, tmp, base);
	}
}

void			parse_value(t_para **glob, char **tmp, t_cmd **base)
{
	int			i;
	char		**cmd;

	i = 0;
	if ((checkifonlyspace((*glob)->cmd) == 1))
	{
		(*glob)->term->action = 0;
		print_prompt((*glob)->env);
	}
	else if ((*glob)->cmd)
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
	free((*glob)->cmd);
}
