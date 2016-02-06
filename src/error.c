#include "minishell.h"

void	invalid_param(char **cmd)
{
	if (ft_strcmp(cmd[0], "setenv") == 0)
		setenv_error(cmd);
}

void	setenv_error(char **cmd)
{
	if (cmd[1] && !cmd[2])
		ft_putendl("To set an environment variable, please add a seconde parameter ex:  USER test");
}

void	ft_notfound(char *cmd)
{
	ft_putstr("minishell: command not found: ");
	ft_putendl(cmd);
}

void	setequal_error()
{
	ft_putendl_fd("You can't set only equal as value parameter in this shell, sorry", 2);
}