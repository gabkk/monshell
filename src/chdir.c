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
	char			*tmp2;
	char			*test;

	ptrmaillon = *env;
	pwd = NULL;
	tmp = NULL;
	nextpwd = NULL;
	i = 0;
	j = 0;
	if (!cmd[1])
		cmd[1] = NULL;
	while (ptrmaillon)
	{
		if (ptrmaillon && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			pwd = (char *)malloc(sizeof(char) * ft_strlen(ptrmaillon->value) + 1);
			pwd = ptrmaillon->value;
			break;
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (pwd)
	{
		if (!cmd[1])
		{
			home = ft_gethome(env);
			ft_setpwd(env, pwd, home);
			free(pwd);
			free(home);
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
			else if (ft_strcmp(cmd[1], "..") == 0)
			{
				tmp = ft_strrchr(pwd, 47);
				i = (ft_strlen(pwd) - ft_strlen(tmp));
				nextpwd = (char *)malloc(sizeof(char) * i);
				while (j < i)
				{
					nextpwd[j] = pwd[j];
					j++;
				}
				nextpwd[j] = '\0';
			}
			else if (strncmp(cmd[1], "../", 3) == 0)
			{
				tmp = ft_strrchr(pwd, 47);
				i = (ft_strlen(pwd) - ft_strlen(tmp));
				ft_putstr("tmp  ->");
				ft_putendl(tmp);
				ft_putnbr(i);
				tmp2 = (char *)malloc(sizeof(char) * i + 1);
				while (j < i)
				{
					tmp2[j] = pwd[j];
					j++;
				}
				tmp2[j] = '\0';
				ft_putstr("tmp2  ->");
				ft_putendl(tmp2);
				tmp = (char*)malloc(sizeof(char)* ft_strlen(cmd[1]) - 1);
				i = 2;
				j = 0;
				while (cmd[1][i] != '\0')
				{
					tmp[j] = cmd[1][i];
					i++;
					j++;
				}
				tmp[i] = '\0';

				nextpwd = ft_strjoin(tmp2, tmp);
				ft_putstr("nextpwd  ->");
				ft_putendl(nextpwd);
				free(tmp2);
			}
			else if (ft_strncmp(cmd[1], "/", 1) == 0)
				nextpwd = ft_strdup(cmd[1]);
			else if (ft_strncmp(cmd[1], "~", 1) == 0)
			{
				home = ft_gethome(env);
//				ft_putendl(home);
//				ft_putendl(pwd);
				if (ft_strncmp(cmd[1], "~/", 2) == 0)
				{
					ft_putendl("ok");
					test = ft_strchr(cmd[1], '/');
					ft_putendl(test);
					nextpwd = ft_strjoin(home, test);
					free(home);
				}
				else
					nextpwd = home;
			}
			else
			{
				ft_putendl("Normal");
				tmp = ft_strjoin(pwd, "/");
				nextpwd = ft_strjoin(tmp, cmd[1]);
				free(tmp);
			}
		}
	}

	if(nextpwd && (directory = opendir(nextpwd)) == NULL)
		ft_putendl_fd("OPENDIR ERROR", 1);
	else
	{
		ft_putendl("Open Success");
		ft_putendl(nextpwd);
		ft_putendl(pwd);
		ft_setpwd(env, pwd, nextpwd);
	}
	free(nextpwd);
	free(pwd);
}

char		*ft_gethome(t_env	**env){
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, "HOME") == 0)
		{
			tmp = ft_strdup(ptrmaillon->value);
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}

// char		*ft_parsebuff(char *buff){
// 	char	*str;
// 	int		i;

// 	i = 0;

// 	str = (char*)malloc(sizeof(char) * ft_strlen(buff));
// 	return (buff);
// }

void		ft_setpwd(t_env **env, char *pwd, char *nextpwd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			if (nextpwd)
			{
				ptrmaillon->value = ft_strdup(nextpwd);
				chdir(nextpwd);
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
