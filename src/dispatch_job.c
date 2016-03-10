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

void			dispatch(t_env **env, char **c)
{
	char		*path;
	char		**tabenv;

	tabenv = NULL;
	if (!c[0])
		return ;
	tabenv = settabenv(env);
	if (b_check(c, env) == 1)
		return (ft_freetab(tabenv));
	else if ((path = iscommande(env, c[0])) != NULL)
	{
		into_fork(path, c, tabenv);
		free(path);
	}
	else if (c[0] && ((islocalexec(c[0]) == 1) || \
		(isexec(c[0], env) == 1)))
	{
		g_flagsignal = -1;
		into_fork(c[0], c, tabenv);
	}
	else if (c[0])
		notfound_error(c[0]);
	ft_freetab(tabenv);
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
				notfound_error(cmd[0]);
		}
		else
			fathersup(father, status);
	}
	else
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putendl_fd(path, 2);
		g_flagsignal = 0;
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
