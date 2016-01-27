#include "minishell.h"

int		main(int ac, char *const av[], char *const envp[])
{
	t_env	*env;

	(void) ac;
	(void) av;
	env = getLocalEnv(envp);
	while(42) {
		char	**cmd;

		cmd = NULL;
		if (!env)
			env = initEnv();
		printPrompt(env);
		cmd = readCommandLine();
		if (*cmd)
		{
			doTheJob(&env, cmd, envp);
		//	free(cmd); //Free toutes les tabs
		}
	}
	return (0);
}

void		doTheJob(t_env **env, char **cmd, char *const envp[]){
	pid_t	father;
	pid_t	w;
	int		status;
	char	**tabenv;
	char	*path;

	(void)envp;
	status = 0;
	tabenv = ft_listintab(env);
	//ft_ptab(tabenv);
	if (isBuiltins(cmd) == 1)
			execBultins(cmd, env, status);
	else if ((path = iscommande(env, cmd)) != NULL)
	{
		if (access(path, X_OK) != -1)
		{
			ft_putendl("got to fork");
			father = fork();
			if (father == -1){
				perror("fork"); //virer perror
				exit(EXIT_FAILURE);
			}
			if (father == 0){
				if ((execve(path, cmd, tabenv) == -1))
				{
					ft_notfound(cmd[0]);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
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
		free(path);
		}
	}
	else
	{
		ft_putstr("END");
		ft_notfound(cmd[0]);
	}
}
