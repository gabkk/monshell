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

int			b_check(char **c, t_env **env)
{
	char	**list_builtins;
	int		i;

	i = 0;
	list_builtins = (char **)malloc(sizeof(char *) * 7);
	list_builtins[0] = "exit";
	list_builtins[1] = "env";
	list_builtins[2] = "setenv";
	list_builtins[3] = "unsetenv";
	list_builtins[4] = "cd";
	list_builtins[5] = "history";
	list_builtins[6] = NULL;
	while (i < 6)
	{
		if (c[0] && env && ft_strcmp(c[0], list_builtins[i]) == 0)
		{
			b_exec(c, env);
			return (1);
		}
		i++;
	}
	free(list_builtins);
	return (0);
}

void		b_exec(char **c, t_env **env)
{
	if (ft_strcmp(c[0], "env") == 0)
	{
		if (c[1] && ft_strcmp(c[1], "-i") == 0)
		{
			g_flagsignal = -1;
			into_fork(c[2], &c[0], NULL);
		}
		else
			showenv(env);
	}
	else if (ft_strcmp(c[0], "cd") == 0)
		ft_opendir(env, c);
	else if (ft_strcmp(c[0], "setenv") == 0)
		add_env(env, c);
	else if (ft_strcmp(c[0], "unsetenv") == 0)
		unset_env(env, c);
	else if (ft_strcmp(c[0], "history") == 0)
		show_history();
	else if (ft_strcmp(c[0], "exit") == 0)
		ft_exit();
}

void		showenv(t_env **env)
{
	t_env	*ptrmaillon;
	int		i;

	i = 17;
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (i < 229)
			randcol_ansi(i++);
		ft_putstr(ptrmaillon->name);
		ft_putstr(ANSI_COLOR_RESET);
		if (ptrmaillon->name && !ptrmaillon->value)
			ft_putendl("=");
		else if (ptrmaillon->name)
			ft_putchar('=');
		if (i < 229)
			randcol_ansi(i++);
		else
			i = 17;
		if (ptrmaillon->value)
			ft_putendl(ptrmaillon->value);
		ft_putstr(ANSI_COLOR_RESET);
		ptrmaillon = ptrmaillon->next;
	}
}

int			isexec(char *cmd, t_env **env)
{
	char	*path;

	path = cmd;
	if (access(path, X_OK) != -1)
	{
		if (ft_strrchr(cmd, '/') != NULL)
		{
			if ((path = iscommande(env, ft_strrchr(cmd, '/') + 1)) != NULL)
				return (1);
		}
	}
	return (0);
}
