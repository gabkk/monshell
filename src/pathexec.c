#include "minishell.h"

int		isCommande(char **cmd){

	if(ft_strcmp(cmd[0], "ls") == 0)
	{
		return(1);
	}
	else if(ft_strcmp(cmd[0], "pwd") == 0)
	{
		return(1);
	}
	return (0);
}