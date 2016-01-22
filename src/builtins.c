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
		ft_putendl(ptrmaillon->value);
		ptrmaillon = ptrmaillon->next;
	}
}

void		addEnv(t_env **env, char **cmd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	if (!cmd[1]){
		execenv(env);
		return;
	} else if (cmd[1] && !cmd[2]){
		while (ptrmaillon){
			if (ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
			ptrmaillon = ptrmaillon->next;
		}
	} else if (cmd[1] && cmd[2]){
		// check si cmd1 si oui modifier cmd2
		// sinon la creer

	}

}









