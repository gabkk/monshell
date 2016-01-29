#include "minishell.h"

int		main(int ac, char *const av[], char *const envp[])
{
	t_env	*env;

	(void) ac;
	(void) av;
	tcgetattr();
	env = getLocalEnv(envp);
	while(42) {
		char	**cmd;

		cmd = NULL;
		if (!env)
			env = setdefaultenv();
//		ft_putendl("out setenv");
		printPrompt(env);
		cmd = readCommandLine();
//		ft_putendl(cmd[0]);
		if (*cmd)
		{
			doTheJob(&env, cmd, envp);
		//	free(cmd); //Free toutes les tabs
		}
		free(cmd);
	}
	return (0);
}
