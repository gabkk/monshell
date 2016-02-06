#include "minishell.h"
#include <sys/types.h>
#include <signal.h>

void		dispatch(t_env **env, char **cmd)
{
	char	*path;
	char	**tabenv;

	tabenv = NULL;
	if (!cmd[0])
		return;
	tabenv = settabenv(env);
	if (builtins_check(cmd, env) == 1)
		return;
	else if ((path = iscommande(env, cmd)) != NULL)
	{
		intothefork(path, cmd, tabenv);
		free(path);
	}
	else if ( cmd[0] && access(cmd[0], X_OK) != -1 )
	{
		flagsignal = -1;
		intothefork(cmd[0], cmd, tabenv);
	}
	else
		ft_notfound(cmd[0]);
	ft_freetab(tabenv);
}


void		intothefork(char *path, char **cmd, char **tabenv)
{
	pid_t	father;
	int		status;

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

void		fathersup(pid_t father, int status)
{
//	pid_t	w;

	if (1 == 2)//test si la commande est en bg
	ft_putstr("back ground job");
	else
	{
		if (flagsignal > 0)
			flagsignal = father;
		else
			flagsignal = 0;
	/*	w = */waitpid(father, &status, WUNTRACED | WCONTINUED);
	}
}
