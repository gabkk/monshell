/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:14:36 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:14:38 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**parse_cmd(char *cmdvalue)
{
	char		**cmdtab;

	if (!(*cmdvalue))
		return (NULL);
	cmdtab = set_tab(cmdvalue);
	if (!cmdtab)
		return (NULL);
	fill_cmd_tab(cmdvalue, cmdtab);
	return (cmdtab);
}

void			fill_cmd_tab(char *cmdvalue, char **cmdtab)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	while (cmdvalue[i] != '\0')
	{
		k = 0;
		while ((cmdvalue[i] != '\0' && ft_isspace(cmdvalue[i]) == 1))
			i++;
		if (cmdvalue[i] != '\0')
			cmdtab[j] = malloc_tab(cmdvalue, i);
		if (cmdtab[j] != NULL)
		{
			while (cmdvalue[i] != '\0' && (ft_isspace(cmdvalue[i]) == 0))
				cmdtab[j][k++] = cmdvalue[i++];
			cmdtab[j][k] = '\0';
		}
		while ((cmdvalue[i] != '\0' && ft_isspace(cmdvalue[i]) == 1))
			i++;
		j++;
	}
	cmdtab[j] = NULL;
}

char			*malloc_tab(char *cmd, int pos)
{
	char		*cmdtab;
	int			len;

	len = 0;
	while (cmd[pos] != '\0' && (ft_isspace(cmd[pos]) == 0))
	{
		pos++;
		len++;
	}
	if (len != 0)
	{
		cmdtab = (char *)malloc(sizeof(char) * len + 1);
		if (!cmdtab)
			return (NULL);
	}
	else
		cmdtab = NULL;
	return (cmdtab);
}

char			**set_tab(char *cmd)
{
	char		**tab;
	int			size;
	int			i;

	i = 0;
	size = 0;
	tab = NULL;
	while (cmd[i] != '\0')
	{
		while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 1))
			i++;
		if (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 0))
		{
			size++;
			while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 0))
				i++;
		}
		while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 1))
			i++;
	}
	if (size != 0)
		tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

void			ft_listintab(t_env **env, char **tabenv)
{
	int			i;
	char		*tmp1;
	t_env		*ptrmaillon;

	i = 0;
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name)
		{
			tmp1 = ft_strjoin(ptrmaillon->name, "=");
			if (ptrmaillon->value)
				tabenv[i] = ft_strjoin(tmp1, ptrmaillon->value);
			else
				tabenv[i] = ft_strdup(tmp1);
			free(tmp1);
			i++;
		}
		ptrmaillon = ptrmaillon->next;
	}
	tabenv[i] = NULL;
}
