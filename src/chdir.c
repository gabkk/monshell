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
	ft_cdaction(env, cmd, home, path);
	free(path);
}

void			ft_cdaction(t_env **env, char **cmd, char *home, char *pwd)
{
	char		*nextpwd;

	nextpwd = NULL;
	if (!cmd[1])
	{
		nextpwd = home;
		if (!nextpwd)
			ft_putendl_fd("No $home variable set", 2);
		else
			ft_opennsave(env, pwd, nextpwd);
	}
	else if (cmd[1])
	{
		if ((nextpwd = ft_setpwd(env, cmd[1], home, pwd, nextpwd)) == NULL)
		{
			ft_opennsave(env, pwd, ft_setmallocpwd(cmd[1], home, pwd));
			free(nextpwd);
			return;
		}
		ft_opennsave(env, pwd, nextpwd);
	}
	else
	 	ft_putendl_fd("too many arguments", 2);
}

void			ft_opennsave(t_env **env, char *pwd, char *nextpwd)
{
	DIR			*directory;

	if ((directory = opendir(nextpwd)) != NULL)
	{
		chdir(nextpwd);
		savepwd(env, pwd, nextpwd);
		closedir(directory);
	}
	else if (ft_strcmp(nextpwd, "error") != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		if (nextpwd && checkifonlyspace(nextpwd) != 1)
			ft_putendl_fd(nextpwd, 2);
		else
			write(1,"\n",1);
	}
}

char			*ft_setpwd(t_env **env, char *cmd, char *home, char *pwd, char *nextpwd)
{
	if (ft_strcmp(cmd, ".") == 0)
		nextpwd = pwd;
	else if (ft_strcmp(cmd, "~") == 0)
	{
		if (!(nextpwd = home))
		{
			ft_putendl_fd("cd: no $home directory", 2);
			return "error";
		}
	}
	else if (ft_strcmp(cmd, "-") == 0)
	{
		if (!(nextpwd = ft_getlistevalue(env, "OLDPWD")))
		{
			ft_putendl_fd("cd: no $OLDPWD value set", 2);
			return "error";
		}
	}
	else if (ft_strcmp(cmd, "/") == 0)
		nextpwd = "/";
	else if (ft_strncmp(cmd, "/", 1) == 0)
		nextpwd = cmd;
	return (nextpwd);
}

char			*ft_setmallocpwd(char *cmd, char *home, char *pwd)
{
	char		*tmp;
	char		*nextpwd;

	nextpwd = NULL;
	if (ft_strncmp(cmd, "~/", 2) == 0)
		nextpwd = ft_strjoin(home, ft_strchr(cmd, '/'));
	else
	{
		tmp = ft_strjoin(pwd, "/");
		nextpwd = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (nextpwd);
}

void			savepwd(t_env **env, char *pwd, char *nextpwd)
{
	t_env		*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		setpwd_maillon(pwd, nextpwd, ptrmaillon);
		ptrmaillon = ptrmaillon->next;
	}
}


void			setpwd_maillon(char *pwd, char *nextpwd, t_env *ptrmaillon)
{
	char		*tmp2;

	if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
	{
		if (nextpwd)
		{
			if (ptrmaillon->value)
				free(ptrmaillon->value);
			tmp2 = (char *)malloc(sizeof (char)* PATH_MAX + 1);
			if (getcwd(tmp2, PATH_MAX) != NULL)
				ptrmaillon->value = ft_strdup(tmp2);
			free(tmp2);
		}
	}
	if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "OLDPWD") == 0)
	{
		if (pwd)
		{
			if (ptrmaillon->value)
				free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(pwd);
		}
	}
}