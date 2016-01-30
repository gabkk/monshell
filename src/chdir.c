#include "minishell.h"

void			ft_opendir(t_env **env, char **cmd)
{
	char		*pwd;
	char		*home;
	char		tmp[PATH_MAX + 1];
	int			havetofree;

	havetofree = 0;
	pwd = ft_getlistevalue(env, "PWD");
	if (!pwd)
	{
		if (getcwd(tmp, PATH_MAX) != NULL)
			pwd = ft_strdup(tmp);
		havetofree = 1;
	}
	home = ft_getlistevalue(env, "HOME");
	ft_cdaction(env, cmd, home, pwd);
	if (havetofree == 1)
		free(pwd);
}

void			ft_cdaction(t_env **env, char **cmd, char *home, char *pwd)
{
	char 		*nextpwd;

	nextpwd = NULL;
	if (cmd[1])
	{
		nextpwd = ft_setpwd(env, cmd[1], home, pwd);
		if (nextpwd == NULL)
		{
			nextpwd = ft_setmallocpwd(cmd[1], home, pwd);
			ft_opennsave(env, pwd, nextpwd);
			free(nextpwd);
			return;
		}
	}
	else if (!cmd[1])
	{
		nextpwd = home;
		if (!nextpwd)
		{
			ft_putendl_fd("No $home variable set", 2);
			return;
		}
	}
	if (ft_strcmp(nextpwd, "error") != 0)
		ft_opennsave(env, pwd, nextpwd);
}

void			ft_opennsave(t_env **env, char *pwd, char *nextpwd){
	DIR			*directory;

	if ((directory = opendir(nextpwd)) != NULL)
	{
		if (ft_getlistevalue(env, "PWD") == NULL)
			chdir(nextpwd);
		ft_savepwd(env, pwd, nextpwd);
		closedir(directory);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(nextpwd, 2);
	}
}

char 			*ft_setpwd(t_env **env, char *cmd, char *home, char *pwd){
	char		*nextpwd;

	nextpwd = NULL;
	if (ft_strcmp(cmd, ".") == 0)
		nextpwd = pwd;
	else if (ft_strcmp(cmd, "~") == 0)
	{
		if (home == NULL)
		{
			ft_putendl_fd("cd: no $home directory", 2);
			nextpwd = "error";
		}
		else
			nextpwd = home;
	}
	else if (ft_strcmp(cmd, "-") == 0)
		nextpwd = ft_getlistevalue(env, "OLDPWD");
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
	int			i;
	int			j;

	nextpwd = NULL;
	if (!(i = 0) && !(j = 1) && ft_strcmp(cmd, "..") == 0)
	{
		i = (ft_strlen(pwd) - ft_strlen(ft_strrchr(pwd, 47)));
		nextpwd = (char *)malloc(sizeof(char) * i);
		while (j++ < i)
			nextpwd[j] = pwd[j];
		nextpwd[j] = '\0';
	}
	else if (ft_strncmp(cmd, "~/", 2) == 0)
		nextpwd = ft_strjoin(home, ft_strchr(cmd, '/'));
	else if (ft_strcmp(cmd, "-") != 0)
	{
		tmp = ft_strjoin(pwd, "/");
		nextpwd = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (nextpwd);
}

void			ft_savepwd(t_env **env, char *pwd, char *nextpwd){
	t_env		*ptrmaillon;
	char		tmp2[PATH_MAX + 1];

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			if (nextpwd)
			{
				chdir(nextpwd);
				if (getcwd(tmp2, PATH_MAX) != NULL)
					ptrmaillon->value = ft_strdup(tmp2);
			}
		}
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "OLDPWD") == 0)
		{
			if (pwd)
				ptrmaillon->value = ft_strdup(pwd);
		}
		ptrmaillon = ptrmaillon->next;
	}
}
