#include "minishell.h"
int		main(int ac, char **av)
{
	t_env	*env;

	(void) ac;
	env = (t_env *)malloc(sizeof(t_env));
	if (!(env))
		return (0);
	getLocalEnv(av, &env);
	while(42) {
		char	**cmd;

		cmd = NULL;
		printPrompt(env);
		cmd = readCommandLine();
		if (cmd[0] != NULL)
		{
			doTheJob(env, cmd);	
			free(cmd); //Free toutes les tabs
		}
	}
	return (0);
}

void		doTheJob(t_env *env, char **cmd){
	pid_t	father;
	int		status;

	if (isBuiltins(cmd) == 1){ //test sur uneliste de builtin
			execBultins(cmd, &env);
		}
		else {
			father = fork();
			if (father == -1){
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (father == 0){
				exit(0);
				ft_putstr("commande");
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
}