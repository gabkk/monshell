#include "minishell.h"
#include <sys/types.h>
#include <signal.h>

void		doTheJob(t_env **env, char **cmd, char **tabenv)
{
	char	*path;

	if (!cmd[0])
		return;
	if (isBuiltins(cmd) == 1)
			execBultins(cmd, env);
	else if ((path = iscommande(env, cmd)) != NULL)
	{
		intothefork(path, cmd, tabenv);
		free(path);
	}
	else if ( cmd[0] && access(cmd[0], X_OK) != -1 )
		intothefork(cmd[0], cmd, tabenv);
	else
		ft_notfound(cmd[0]);
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

void	fathersup(pid_t father, int status)
{
	pid_t	w;

	if (1 == 2)//test si la commande est en bg
	ft_putstr("back ground job");
	else
	{
		w = waitpid(father, &status, WUNTRACED | WCONTINUED);
		// ft_putstr("status : ");
		// ft_putnbr(status);
		// ft_putstr("pid : ");
		// ft_putnbr(w);






		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			if (w == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(status)) {
			printf("exited, status=%d\n", WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {
			printf("killed by signal %d\n", WTERMSIG(status));
			} else if (WIFSTOPPED(status)) {
			printf("stopped by signal %d\n", WSTOPSIG(status));
			} else if (WIFCONTINUED(status)) {
			printf("continued\n");
			}
		}
		kill(w, SIGKILL);

	}

}

















