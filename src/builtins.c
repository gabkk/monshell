/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:21:12 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:21:14 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtins_check(char **cmd, t_env **env)
{
	char	**list_builtins;
	int		i;

	i = 0;
	list_builtins = (char **)malloc(sizeof(char *) * 6);
	list_builtins[0] = "exit";
	list_builtins[1] = "env";
	list_builtins[2] = "setenv";
	list_builtins[3] = "unsetenv";
	list_builtins[4] = "cd";
	list_builtins[5] = NULL;
	while (i < 5)
	{
		if (cmd[0] && ft_strcmp(cmd[0], list_builtins[i]) == 0)
		{
			builtins_exec(cmd, env);
			return (1);
		}
		i++;
	}
	free(list_builtins);
	return (0);
}

void		builtins_exec(char **cmd, t_env **env)
{
	if (env && cmd[0] != NULL)
	{
		if (ft_strcmp(cmd[0], "env") == 0)
		{
			if (cmd[1] && ft_strcmp(cmd[1], "-i") == 0)
			{
				g_flagsignal = -1;
				into_fork(cmd[2], &cmd[0], getdefaultenv());
			}
			else
				showenv(env);
		}
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_opendir(env, cmd);
		else if (ft_strcmp(cmd[0], "setenv") == 0)
			add_env(env, cmd);
		else if (ft_strcmp(cmd[0], "unsetenv") == 0)
			unset_env(env, cmd);
		else if (ft_strcmp(cmd[0], "exit") == 0)
		{
			ft_putendl("exit");
			freenv(*env);
			exit(0);
		}
	}
}

void		showenv(t_env **env)
{
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		ft_putstr(ptrmaillon->name);
		if (ptrmaillon->name && !ptrmaillon->value)
			ft_putendl("=");
		else if (ptrmaillon->name)
			ft_putchar('=');
		if (ptrmaillon->value)
			ft_putendl(ptrmaillon->value);
		ptrmaillon = ptrmaillon->next;
	}
}
