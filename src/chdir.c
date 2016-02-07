/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:23:03 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:23:04 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_opendir(t_env **env, char **cmd)
{
	char		*home;
	char		*path;
	char		*tmp;

	path = NULL;
	home = ft_getlistevalue(env, "HOME");
	tmp = (char *)malloc(sizeof(char) * PATH_MAX + 1);
	if (getcwd(tmp, PATH_MAX) != NULL)
		path = ft_strdup(tmp);
	free(tmp);
	cd_cmd(env, cmd, home, path);
	free(path);
}

void			cd_cmd(t_env **env, char **cmd, char *home, char *pwd)
{
	char		*nextpwd;

	nextpwd = NULL;
	if (!cmd[1])
	{
		nextpwd = home;
		if (!nextpwd)
			ft_putendl_fd("No $home variable set", 2);
		else
			open_n_save(env, pwd, nextpwd);
	}
	else if (cmd[1])
	{
		if ((nextpwd = set_pwd(env, cmd[1], pwd, nextpwd)) == NULL)
		{
			open_n_save(env, pwd, ft_setmallocpwd(cmd[1], home, pwd));
			free(nextpwd);
			return ;
		}
		open_n_save(env, pwd, nextpwd);
	}
	else
		ft_putendl_fd("too many arguments", 2);
}

void			open_n_save(t_env **env, char *pwd, char *nextpwd)
{
	DIR			*directory;
	t_env		*ptrmaillon;

	if ((directory = opendir(nextpwd)) != NULL)
	{
		chdir(nextpwd);
		ptrmaillon = *env;
		while (ptrmaillon)
		{
			setenv_maillon(pwd, nextpwd, ptrmaillon);
			ptrmaillon = ptrmaillon->next;
		}
		closedir(directory);
	}
	else if (nextpwd && ft_strcmp(nextpwd, "error") != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		if (nextpwd && checkifonlyspace(nextpwd) != 1)
			ft_putendl_fd(nextpwd, 2);
		else
			write(1, "\n", 1);
	}
}

char			*set_pwd(t_env **env, char *cmd, char *pwd, char *np)
{
	char		*home;

	home = ft_getlistevalue(env, "HOME");
	if (ft_strcmp(cmd, ".") == 0)
		np = pwd;
	else if (ft_strcmp(cmd, "~") == 0)
	{
		if (!(np = home))
		{
			ft_putendl_fd("cd: no $home directory", 2);
			return ("error");
		}
	}
	else if (ft_strcmp(cmd, "-") == 0)
	{
		if (!(np = ft_getlistevalue(env, "OLDPWD")))
			return (oldpwd_error());
	}
	else if (ft_strcmp(cmd, "/") == 0)
		np = "/";
	else if (ft_strncmp(cmd, "/", 1) == 0)
		np = cmd;
	return (np);
}

char			*ft_setmallocpwd(char *cmd, char *home, char *pwd)
{
	char		*tmp;
	char		*nextpwd;

	nextpwd = NULL;
	if (ft_strncmp(cmd, "~/", 2) == 0)
	{
		if (!home)
			return (NULL);
		nextpwd = ft_strjoin(home, ft_strchr(cmd, '/'));
	}
	else
	{
		tmp = ft_strjoin(pwd, "/");
		nextpwd = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (nextpwd);
}
