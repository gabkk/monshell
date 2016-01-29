#include "minishell.h"
void		doTheJob(t_env **env, char **cmd, char *const envp[])
{

	char	**tabenv;
	char	*path;

	(void)envp;
	//pathtmp = setpathtmp();
	tabenv = ft_listintab(env);
	if (!tabenv)
		tabenv = getdefaultenv();
	if (isBuiltins(cmd) == 1)
			execBultins(cmd, env);
	else if ((path = iscommande(env, cmd)) != NULL)
	{
		intothefork(path, cmd, tabenv);
		free(path);
	}
	else if ( access(cmd[0], X_OK) != -1 )
	{
		//ft_putendl("PAsse ici");
		// setlistlvl(env);
		// if (tabenv)
		// 	free(tabenv);
		// tabenv = ft_listintab(env);
		intothefork(cmd[0], cmd, tabenv);
	}
	else
	{
		ft_putendl("END");
		ft_notfound(cmd[0]);
	}
}


void		intothefork(char *path, char **cmd, char **tabenv)
{
	pid_t	father;
	int		status;

	status = 0;
	if (access(path, X_OK) != -1)
	{
		//ft_putendl("got to fork");
		father = fork();
		if (father == -1){
			perror("fork"); //virer perror
			exit(EXIT_FAILURE);
		}
		if (father == 0){
			//setshlvl(tabenv);
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
	}
}

















