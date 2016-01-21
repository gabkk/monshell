#include "minishell.h"

int			isBuiltins(char *cmd){
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
		if (ft_strcmp(cmd, listBuiltins[i]) == 0){
			boolean = 1;
			break;
		}
		boolean = 0;
		i++;
	}
	free(listBuiltins);
	return boolean;
}

void		execBultins(char *cmd, t_env **env){

	if (ft_strcmp(cmd, "env") == 0){
		execenv(env);
	}
}

void		execenv(t_env **env){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon){
		ft_putstr(ptrmaillon->name);
		ft_putchar('=');
		ft_putendl(ptrmaillon->value);
		ptrmaillon = ptrmaillon->next;
	}
}