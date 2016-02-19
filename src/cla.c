/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cla.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			addlmaillon(char **cmd, t_cmd **liste)
{
	t_cmd		*newmaillon;
	t_cmd		*ptrmaillon;

	if (!(*cmd))
		return ;
	newmaillon = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(newmaillon))
		return ;
	newmaillon->listcmd = NULL;
	newmaillon->next = NULL;
	if (!(*liste))
	{
		*liste = newmaillon;
		newmaillon->listcmd = cmd;
		newmaillon->next = NULL;
		return ;
	}
	ptrmaillon = *liste;
	while (ptrmaillon->next)
		ptrmaillon = ptrmaillon->next;
	ptrmaillon->next = newmaillon;
	newmaillon->listcmd = cmd;
	newmaillon->next = NULL;
}

void			read_command_line(t_cmd **base)
{
	char		*value;
	char		**tmp;

	value = NULL;
	tmp = NULL;
	if (get_next_line(STDIN_FILENO, &value) == 0)
	{
		ft_putendl("exit");
		free(value);
		exit(0);
	}
	if (*value)
		add_to_history(value);
	parse_value(value, tmp, base);
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
				addlmaillon(tmp, base);
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
	free(value);
}
