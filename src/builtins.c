#include "minishell.h"

int			isBuiltins(char **cmd){
	char	**listBuiltins;
	int		i;
	int		boolean;

	i = 0;
	listBuiltins = (char **)malloc(sizeof(char*) * 5);
	listBuiltins[0] = "exit";
	listBuiltins[1] = "env";
	listBuiltins[2] = "setenv";
	listBuiltins[3] = "unsetenv";
	listBuiltins[4] = "cd";
	while (i < 5){
		if (ft_strcmp(cmd[0], listBuiltins[i]) == 0){
			boolean = 1;
			break;
		}
		boolean = 0;
		i++;
	}
	free(listBuiltins);
	return boolean;
}

void		execBultins(char **cmd, t_env **env, int status){

	if (env)
	{
		if (ft_strcmp(cmd[0], "env") == 0)
			showenv(env);
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_opendir(env, cmd);
		else if (ft_strcmp(cmd[0], "setenv") == 0)
			addEnv(env, cmd);
		else if (ft_strcmp(cmd[0], "unsetenv") == 0)
			unset_env(env, cmd);
		else if (ft_strcmp(cmd[0], "exit") == 0)
		{
			// GERER LES FREE EN EXIT
			exit(status);
		}
	}
}

void		showenv(t_env **env){
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
