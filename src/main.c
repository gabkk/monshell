#include "minishell.h"


int				main(int ac, char *const av[], char *const envp[])
{
	t_env		*env;

	env = NULL;
	(void) ac;
	(void) av;
	env = getlocalenv(envp);
	if (env)
		setlistlvl(&env);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putendl("sig error");
	mainbody(env);
	freenv(env);
	return (0);
}
