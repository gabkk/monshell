#include "minishell.h"

int				main(int ac, char *const av[], char *const envp[])
{
	t_env		*env;
	t_cmd		*base;

	(void) ac;
	(void) av;
	env = getlocalenv(envp);
	setlistlvl(&env);
	while(42)
	{
		base =  NULL;
		if (!env)
			env = setdefaultenv();
		printPrompt(env);
		readCommandLine(&base);
		if (base)
		{
			while (base)
			{
				doTheJob(&env, base->listcmd);
				base = base->next;
			}
		//	free(cmd); //Free toutes les tabs
		}
		//free(cmd); free tout le details
	}
	return (0);
}
