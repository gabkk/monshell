/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:52:38 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:52:41 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			mainbody(t_env *env)
{
	t_cmd		*base;
	t_cmd		*ptrmaillon;

	base = NULL;
	g_flagsignal = 0;
	if (!env)
		env = setdefaultenv();
	while (42)
	{
		print_prompt(env);
		read_command_line(&base);
		if (base)
		{
			ptrmaillon = base;
			while (ptrmaillon)
			{
				if (ptrmaillon->listcmd)
					dispatch(&env, ptrmaillon->listcmd);
				ptrmaillon = ptrmaillon->next;
			}
			freebase(&base);
		}
	}
}

void			dispatch(t_env **env, char **cmd)
{
	char		*path;
	char		**tabenv;

	tabenv = NULL;
	if (!cmd[0])
		return ;
	tabenv = settabenv(env);
	if (builtins_check(cmd, env) == 1)
		return ;
	else if ((path = iscommande(env, cmd)) != NULL)
	{
		into_fork(path, cmd, tabenv);
		free(path);
	}
	else if (cmd[0] && access(cmd[0], X_OK) != -1)
	{
		g_flagsignal = -1;
		into_fork(cmd[0], cmd, tabenv);
	}
	else
		ft_notfound(cmd[0]);
	ft_freetab(tabenv);
}

char			**settabenv(t_env **env)
{
	int			i;
	t_env		*ptrmaillon;
	char		**tabenv;

	tabenv = NULL;
	i = 0;
	if (*env)
	{
		ptrmaillon = *env;
		while (ptrmaillon)
		{
			i++;
			ptrmaillon = ptrmaillon->next;
		}
		tabenv = (char **)malloc(sizeof(char *) * (i + 1));
		ft_listintab(env, tabenv);
	}
	else
		tabenv = getdefaultenv();
	return (tabenv);
}

void			into_fork(char *path, char **cmd, char **tabenv)
{
	pid_t		father;
	int			status;

	status = 0;
	if (access(path, X_OK) != -1)
	{
		father = fork();
		if (father == -1)
			exit(EXIT_FAILURE);
		if (father == 0)
		{
			if (execve(path, cmd, tabenv) == -1)
			{
				ft_putendl("exec fail");
				ft_notfound(cmd[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			fathersup(father, status);
	}
}

void			fathersup(pid_t father, int status)
{
	if (1 == 2)
		ft_putstr("back ground job");
	else
	{
		if (g_flagsignal > 0)
			g_flagsignal = father;
		else
			g_flagsignal = 0;
		waitpid(father, &status, WUNTRACED | WCONTINUED);
	}
}
