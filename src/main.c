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

void			mainbody(t_env *env)
{
	t_cmd		*base;
	t_cmd		*ptrmaillon;

	base =  NULL;
	flagsignal = 0;
	if (!env)
		env = setdefaultenv();
	while(42)
	{
		printPrompt(env);
		readCommandLine(&base);
		if (base)
		{
			ptrmaillon = base;
			while (ptrmaillon)
			{
				if (ptrmaillon->listcmd)
					dispatch(&env, ptrmaillon->listcmd);
				ptrmaillon = ptrmaillon->next;
			}			
			freebase(&base);
		}
	}
}


char			**settabenv(t_env **env)
{
	int 	i;
	t_env	*ptrmaillon;
	char **tabenv;
	
	tabenv = NULL;
	i = 0;
	if (*env)
	{
		ptrmaillon = *env;
		while (ptrmaillon)
		{
			i++;
			ptrmaillon = ptrmaillon->next;
		}
		tabenv = (char **)malloc(sizeof(char *) * (i + 1));
		ft_listintab(env, tabenv);
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
		if ((*base)->listcmd)
			ft_freetab((*base)->listcmd);
		ptrmaillon = (*base)->next;
		free(*base);
		*base = ptrmaillon;
	}
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