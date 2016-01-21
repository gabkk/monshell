#include "minishell.h"
int		main(int ac, char **av)
{
	t_env	**env;

	env = getLocalEnv(av);
	(void) ac;
	while(42) {
		pid_t	father;
		int		status;
		char	*cmd;

		(void)av;
		printPrompt();
		cmd = readCommandLine();
		// readline open un fd sur l entree standart
		// read l entree standart et la stocker dans un char*

		if (isBuiltins(cmd) == 1){ //test sur uneliste de builtin
			execBultins(cmd, env);
			ft_putendl("built-in");
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
	return (0);
}
