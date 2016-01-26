#include "minishell.h"

void		ft_opendir(t_env **env, char **cmd){
	t_env			*ptrmaillon;
	DIR				*directory;
	char			*pwd;
	char			*tmp;
	char 			*nextpwd;
	char			*home;
	int				i;
	int				j;
	char			*test;

	ptrmaillon = *env;
	pwd = NULL;
	tmp = NULL;
	nextpwd = NULL;
	home = NULL;
	i = 0;
	j = 0;
	if (!cmd[1])
		cmd[1] = NULL;
	while (ptrmaillon)
	{
		if (ptrmaillon && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			pwd = ptrmaillon->value;
			break;
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (pwd)
	{
		if (!cmd[1]) //fine but check leacks
		{
			home = ft_gethome(env);
			ft_setpwd(env, pwd, home);
			return ;
		}
		if (cmd[1])
		{
			if (ft_strcmp(cmd[1], ".") == 0)
			{	
				if((directory = opendir(pwd)) == NULL)
					ft_putendl_fd("OPENDIR ERROR", 1);
				else
					ft_setpwd(env, NULL, NULL);
				return;
			}
			else if (ft_strcmp(cmd[1], "~") == 0)
			{
				home = ft_gethome(env);
				ft_putstr("home");
				ft_putendl(home);
			
				nextpwd = home;
				ft_putendl(nextpwd);
			}
			else if (ft_strcmp(cmd[1], "..") == 0)
			{
				ft_putendl("dotdot..");
				tmp = ft_strrchr(pwd, 47);
				i = (ft_strlen(pwd) - ft_strlen(tmp));
				nextpwd = (char *)malloc(sizeof(char) * i); //free
				while (j < i)
				{
					nextpwd[j] = pwd[j];
					j++;
				}
				nextpwd[j] = '\0';
			}
			else if (ft_strcmp(cmd[1], "/"))
				nextpwd = "/";
			else if (ft_strncmp(cmd[1], "/", 1) == 0)
				nextpwd = cmd[1];
			else if (ft_strncmp(cmd[1], "~/", 2) == 0)
			{
				ft_putendl("ok");
				test = ft_strchr(cmd[1], '/');
				ft_putendl(test);
				nextpwd = ft_strjoin(home, test);//free
			}
			else
			{
				ft_putendl("Normal");
				tmp = ft_strjoin(pwd, "/");
				nextpwd = ft_strjoin(tmp, cmd[1]);//free
				free(tmp);
			}
		}
	}

	if(nextpwd && (directory = opendir(nextpwd)) == NULL)
	{
		ft_putendl_fd("OPENDIR ERROR", 1);
		ft_putendl(nextpwd);
		return;
	}
	else
	{
		ft_putendl("Open Success");
		ft_putendl(nextpwd);
		ft_putendl(pwd);
		ft_setpwd(env, pwd, nextpwd);
	}
}

char		*ft_gethome(t_env	**env){
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, "HOME") == 0)
		{
			tmp = ptrmaillon->value;
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}

void		ft_setpwd(t_env **env, char *pwd, char *nextpwd){
	t_env	*ptrmaillon;
	char	*tmp2;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			if (nextpwd)
			{
				chdir(nextpwd);
				tmp2 = (char *)malloc(sizeof(char) * 100);
				if (getcwd(tmp2, 99) != NULL)
				ptrmaillon->value = ft_strdup(tmp2);
				free(tmp2);
				ft_putendl(ptrmaillon->value);
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
