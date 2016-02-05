#include "minishell.h"


int				main(int ac, char *const av[], char *const envp[])
{

	env = NULL;
	(void) ac;
	(void) av;


  	env = getlocalenv(envp);
	if (env)
		setlistlvl(&env);

  	mainbody(env);
	freenv(env);   //------------
	return (0);
}

void			mainbody(t_env *env)
{
	t_cmd		*base;
	t_cmd		*ptrmaillon;
	char		**tabenv;



	tabenv = NULL;
	base =  NULL;
	while(42)
	{
		if (signal(SIGINT, sig_handler) == SIG_ERR)
			ft_putendl("sig error");
		if (!env)
			env = setdefaultenv();
		printPrompt(env);
		readCommandLine(&base);
		if (base)
		{
			ptrmaillon = base;
			while (ptrmaillon)
			{
				//ft_putendl("cmd boucle");
				tabenv = settabenv(env);
				if (ptrmaillon->listcmd)
					doTheJob(&env, ptrmaillon->listcmd, tabenv);
				ft_freetab(tabenv);
				//ft_ptab(ptrmaillon->listcmd);
				//ft_freetab(ptrmaillon->listcmd);         //---------
				ptrmaillon = ptrmaillon->next;
			}			
			freebase(&base); // fou la merde a checker //---------
		}
		// ft_putstr("commande :");
		// ft_putendl(ptrmaillon->listcmd[0]);
		//free(base);// verfier ce truc
		//close(STDIN_FILENO);
	}
}


char			**settabenv(t_env *env)
{
	int 	i;
	t_env	*ptrmaillon;
	char **tabenv;
	
	tabenv = NULL;
	i = 0;
	if (env)
	{
		ptrmaillon = env;
		while (ptrmaillon)
		{
			i++;
			ptrmaillon = ptrmaillon->next;
		}
		tabenv = (char **)malloc(sizeof(char *) * (i + 1));
		ft_listintab(&env, tabenv);
	}
	else
	 	tabenv = getdefaultenv();
	return (tabenv);
}

void			freebase(t_cmd	**base)
{
	t_cmd		*ptrmaillon;

	if (!base || !*base)
		return;
	while (*base)
	{
		//ft_putstr("yo");
		if ((*base)->listcmd)
			ft_freetab((*base)->listcmd);
		ptrmaillon = (*base)->next;
		free(*base);
		*base = ptrmaillon;
	}
	// if (*base)
	// {
	// 	ft_freetab((*base)->listcmd);
	// 	free(*base);
	// }
	*base = NULL;
}

void			freenv(t_env	*env)
{
	t_env		*ptrmaillon;

	while (env != NULL)
	{
		free(env->name);
		if (env->value)
			free(env->value);
		ptrmaillon = env;
		free(env);
		env = ptrmaillon->next;
	}
}