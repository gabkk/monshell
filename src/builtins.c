#include "minishell.h"

int			builtins_check(char **cmd, t_env **env)
{
	char	**listBuiltins;
	int		i;

	i = 0;
	listBuiltins = (char **)malloc(sizeof (char *) * 6);
	listBuiltins[0] = "exit";
	listBuiltins[1] = "env";
	listBuiltins[2] = "setenv";
	listBuiltins[3] = "unsetenv";
	listBuiltins[4] = "cd";
	listBuiltins[5] = NULL;
	while (i < 5)
	{
		if (cmd[0] && ft_strcmp(cmd[0], listBuiltins[i]) == 0)
		{
			builtins_exec(cmd, env);
			return 1;
		}
		i++;
	}
	free(listBuiltins);
	return 0;
}

void		builtins_exec(char **cmd, t_env **env)
{
	if (env && cmd[0] != NULL)
	{
		if (ft_strcmp(cmd[0], "env") == 0)
		{
			if (cmd[1] && ft_strcmp(cmd[1], "-i") == 0)
			{
				flagsignal = -1;
				into_fork(cmd[2], &cmd[0], getdefaultenv());
			}
			else
				showenv(env);
		}
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_opendir(env, cmd);
		else if (ft_strcmp(cmd[0], "setenv") == 0)
			add_env(env, cmd);
		else if (ft_strcmp(cmd[0], "unsetenv") == 0)
			unset_env(env, cmd);
		else if (ft_strcmp(cmd[0], "exit") == 0)
		{
			ft_putendl("exit");//penser a tout free
			freenv(*env);
			exit(0);
		}
	}
}

void		showenv(t_env **env)
{
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon){
		ft_putstr(ptrmaillon->name);
		if (ptrmaillon->name && !ptrmaillon->value)
			ft_putendl("=");
		else if (ptrmaillon->name)
			ft_putchar('=');
		if (ptrmaillon->value)
			ft_putendl(ptrmaillon->value);
		ptrmaillon = ptrmaillon->next;
	}
}
