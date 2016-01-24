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
//		ft_putendl("");
		if (!env){
			env = initEnv();
//			ft_putendl("PAD D ENV");
		}
		printPrompt(env);
		cmd = readCommandLine();
//		ft_putendl("sortit");
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
	int		status;

	if (isBuiltins(cmd) == 1)
	{ //test sur uneliste de builtin
			execBultins(cmd, env);
//			ft_putstr("out of builtin");
	}
	else if (isCommande(cmd) == 1)
	{
		father = fork();
		if (father == -1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (father == 0){
			ft_putstr("commande");
			if(ft_strcmp(cmd[0], "ls") == 0)
				execve("/bin/ls", cmd, envp);
			else if(ft_strcmp(cmd[0], "pwd") == 0)
				execve("/bin/pwd", cmd, envp);
		}else{
			if (1 == 2)//test si la commande est en bg
			ft_putstr("back ground job");
			else {
				waitpid(father, &status, WUNTRACED | WCONTINUED);
				// while (!WIFEXITED(status) && !WIFSIGNALED(status)){
				// 	w = 

				// 	if (w == -1) {
				// 		perror("waitpid");
				// 		exit(EXIT_FAILURE);
				// 	}

				// 	if (WIFEXITED(status)) {
				// 	printf("exited, status=%d\n", WEXITSTATUS(status));
				// 	} else if (WIFSIGNALED(status)) {
				// 	printf("killed by signal %d\n", WTERMSIG(status));
				// 	} else if (WIFSTOPPED(status)) {
				// 	printf("stopped by signal %d\n", WSTOPSIG(status));
				// 	} else if (WIFCONTINUED(status)) {
				// 	printf("continued\n");
				// 	}

			}
		}
	}
	else 
	{
		ft_putendl_fd("Commande non reconnue", 2);
	}
}







	// char	**tabenv;
	// int 	i;
	// t_env	*ptrmaillon;

	// i = 0;
	// ptrmaillon = *env;
	// while (ptrmaillon)
	// {
	// 	i++;
	// 	ptrmaillon = ptrmaillon->next;
	// }
	// tabenv = (char **)malloc(sizeof(char *) * i);
	// ptrmaillon = *env;
	// i = 0;
	// while (ptrmaillon)
	// {
	// 	if (ptrmaillon)
	// 	{
	// 		tabenv[i] = (char *)malloc(sizeof(char) * ft_strlen());

	// 	}
	// 	ptrmaillon = ptrmaillon->next;
	// }
