#include "minishell.h"

void			ft_opendir(t_env **env, char **cmd){ // Reprendre des choses pas claire
	char		*pwd;
	char 		*nextpwd;
	char		*home;
	char		*tmp;
	int			havetofree; //faire plus propre

	havetofree = 0;
	nextpwd = NULL;
	pwd = ft_getlistevalue(env, "PWD");
	if (!pwd)
	{
	//	ft_putendl("Pas de PWD");
		tmp = (char *)malloc(sizeof(char) * 100); // mettre une valeur correct dans le buffer
		if (getcwd(tmp, 99) != NULL)
		pwd = ft_strdup(tmp);
		free(tmp);
	//	ft_putendl(pwd);
		havetofree = 1;
	}
	home = ft_getlistevalue(env, "HOME");
	if (cmd[1])
	{
		nextpwd = ft_setpwd(env, cmd[1], home, pwd);
		if (nextpwd == NULL)
		{
			nextpwd = ft_setmallocpwd(cmd[1], home, pwd);
	//		ft_putstr("AFTER ft_setmallocpwd --- >  ");
	//		ft_putendl(nextpwd);
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
	if (havetofree == 1)
		free(pwd);
}

void			ft_opennsave(t_env **env, char *pwd, char *nextpwd){
	DIR			*directory;

	if((directory = opendir(nextpwd)) != NULL)
	{
	//	ft_putstr("inside ft_opensave --- >  ");
	//	ft_putendl(nextpwd);
		if (ft_getlistevalue(env, "PWD") == NULL)
			chdir(nextpwd);
		ft_savepwd(env, pwd, nextpwd);
		closedir(directory);
	}
	else
		ft_putendl_fd("OPENDIR ERROR ici", 2); // mettre le bon retour
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
			ft_putendl_fd("cd: no home directory", 2);
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

	if (!(i = 0) && !(j = 0) && ft_strcmp(cmd, "..") == 0)
	{
	//	ft_putstr("ft_setmallocpwd ---- > ");
	//	ft_putendl(pwd);
		i = (ft_strlen(pwd) - ft_strlen(ft_strrchr(pwd, 47)));
		nextpwd = (char *)malloc(sizeof(char) * i);
		while (j < i)
		{
			nextpwd[j] = pwd[j];
			j++;
		}
		nextpwd[j] = '\0';
	}
	else if (ft_strncmp(cmd, "~/", 2) == 0)
		nextpwd = ft_strjoin(home, ft_strchr(cmd, '/'));
	else
	{
		tmp = ft_strjoin(pwd, "/");
		nextpwd = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (nextpwd);
}

void		ft_savepwd(t_env **env, char *pwd, char *nextpwd){
	t_env	*ptrmaillon;
	char	*tmp2;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			if (nextpwd)
			{
	//			ft_putstr("Avant chdir ---->  ");
	//			ft_putendl(nextpwd);
				chdir(nextpwd);
				tmp2 = (char *)malloc(sizeof(char) * 100); // mettre une valeur correct dans le buffer
				if (getcwd(tmp2, 99) != NULL)
				ptrmaillon->value = ft_strdup(tmp2);
				free(tmp2);
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
