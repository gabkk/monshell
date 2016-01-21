#include "minishell.h"

int			isBuiltins(char **cmd){
	char	**listBuiltins;
	int		i;
	int		boolean;


	//ft_putendl(cmd[0]); // virer ce put
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

void		execBultins(char **cmd, t_env **env){

	ft_putstr(cmd[0]); // virer ce put
	if (ft_strcmp(cmd[0], "env") == 0){
		execenv(env);
	} else if (ft_strcmp(cmd[0], "setenv") == 0){
		builtSetEnv(env);
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

void		builtSetEnv(t_env **env){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon){

		ptrmaillon = ptrmaillon->next;
	}
}









