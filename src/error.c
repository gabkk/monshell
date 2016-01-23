#include "minishell.h"

void invalidParam(char **cmd){
	if (strcmp(cmd[0], "setenv") == 0){
		setenvError(cmd);
	}
}

void	setenvError(char **cmd){
	if (cmd[1] && !cmd[2]){
		ft_putendl("To set an environment variable, please add a seconde parameter ex:  USER test");
	}
}
