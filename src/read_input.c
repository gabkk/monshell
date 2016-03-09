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

void			read_command_line(t_cmd **base)
{
	char		*value;
	char		**tmp;
	int			ret;

	value = NULL;
	tmp = NULL;
	ret = 0;
	if ((ret = get_next_line(STDIN_FILENO, &value)) == 0)
	{
		ft_putendl("exit");
		free(value);
		exit(0);
	}
	else if (ret == -1)
		exit(EXIT_FAILURE);
	else
	{
		if (*value)
			add_to_history(value);
		parse_value(value, tmp, base);
	}
}

void			parse_value(char *value, char **tmp, t_cmd **base)
{
	int			i;
	char		**cmd;

	i = 0;
	if ((checkifonlyspace(value) == 1))
	{
		free(value);
		return ;
	}
	if (*value)
	{
		cmd = ft_strsplit(value, ';');
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
	free(value);
}
