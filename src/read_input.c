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

void			read_input(t_env **e, t_input **input)
{
	char	buff[4];
	int		index;

	index = 0;
	read((*e)->fd, buff, 4);
	if (buff[0] != '\n' && ft_isprint(buff[0]))
	{
		ft_putchar_fd(buff[0], (*e)->fd);
		add_to_lst_input(input, buff[0], index);
	}
	else if (buff[0] == 27)
	{
		if (buff[0] == 27)
		{
			//key-arrow
			ft_putendl_fd("F", (*e)->fd);
			//exit(0);			
		}
		else if (buff[0] == 127 || (buff[0] == 27 && buff[2] == '3'))//del
			ft_putendl_fd("delete", (*e)->fd);
		ft_bzero(buff, 4);
		return ;
	}
	else if (buff[0] == '\n')//line
	{

		ft_putendl_fd(" ", (*e)->fd);
		print_lst_input(input, e);
		//delete free la liste input
		delete_lst_input(input);
		(*e)->term->action = 1;
	}
	ft_bzero(buff, 4);
}

void			read_cmd(t_env **env, t_cmd **base)
{
	char		**tmp;

	tmp = NULL;
	if ((*env)->value)
	{
		add_to_history((*env)->value);
		parse_value(env, tmp, base);
	}
}

void			parse_value(t_env **env, char **tmp, t_cmd **base)
{
	int			i;
	char		**cmd;

	i = 0;
	if ((checkifonlyspace((*env)->value) == 1))
	{
		free((*env)->value);
		(*env)->term->action = 0;
		print_prompt(*env);
		return ;
	}
	if ((*env)->value)
	{
		cmd = ft_strsplit((*env)->value, ';');
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
		free((*env)->value);
	}
}
