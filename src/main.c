#include "minishell.h"

int		main(int ac, char *const av[], char *const envp[])
{
	t_env	*env;
	t_cmd		*base;

	(void) ac;
	(void) av;
	//tcgetattr();
	env = getLocalEnv(envp);
	setlistlvl(&env);
	while(42)
	{
		base =  NULL;
		if (!env)
			env = setdefaultenv();
//		ft_putendl("out setenv");
		printPrompt(env);
		readCommandLine(&base);

//		t_cmd		*ptrmaillon;

	// ptrmaillon = base;
	// while (ptrmaillon)
	// {
	// 	ft_putendl("liste : ");
	// 	ft_ptab(ptrmaillon->listcmd);
	// 	ptrmaillon = ptrmaillon->next;
	// 	ft_putendl("");
	// }

	//	ft_putendl("inthe main");

		if (base)
		{
	//	ft_putendl("inthe main");

			while (base)
			{
				doTheJob(&env, base->listcmd, envp);
				base = base->next;
			}
		//	free(cmd); //Free toutes les tabs
		}
		//free(cmd); free tout le details
	}
	return (0);
}
