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
	//free(listBuiltins);
	return boolean;
}

void		execBultins(char **cmd, t_env **env){

	if (ft_strcmp(cmd[0], "env") == 0){
		execenv(env);
	} else if (ft_strcmp(cmd[0], "setenv") == 0){
		addEnv(env, cmd);
	}
}

void		execenv(t_env **env){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon){
		ft_putstr(ptrmaillon->name);
		ft_putchar('=');
		(ptrmaillon->value) ? ft_putendl(ptrmaillon->value) : ft_putchar('\n');
		ptrmaillon = ptrmaillon->next;
	}
}
