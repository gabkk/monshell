/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:50:04 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:50:06 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_param(char **cmd)
{
	if (ft_strcmp(cmd[0], "setenv") == 0)
		setenv_error(cmd);
}

void	setenv_error(char **cmd)
{
	if (cmd[1] && !cmd[2])
		ft_putendl("To set an environment variable, please add\
a seconde parameter ex:  USER test");
}

void	ft_notfound(char *cmd)
{
	ft_putstr("minishell: command not found: ");
	ft_putendl(cmd);
}

void	setequal_error(void)
{
	ft_putendl_fd("You can't set only equal as value parameter\
in this shell, sorry", 2);
}

char	*oldpwd_error(void)
{
	ft_putendl_fd("cd: no $OLDPWD value set", 2);
	return ("error");
}
