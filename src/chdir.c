#include "minishell.h"

void		ft_opendir(t_env **env, char **cmd){
	t_env			*ptrmaillon;
//	char			*value;
//	int				fd;
//	int				buff;
	DIR				*directory;
	char			*pwd;
	char			*tmp;
	char 			*nextpwd;
	t_dirent		dir;

	(void)cmd;
//	buff = 90; // regler les problemes de buffer
	ptrmaillon = *env;
//	if (ft_strcmp(cmd[1], "."))
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
	if (!pwd)
		return;
	tmp = ft_strjoin(pwd, "/");
	free(pwd);
	nextpwd = ft_strjoin(tmp, cmd[1]);
	ft_putstr("nexpwd  ->  ");
	ft_putendl(nextpwd);
	ft_putstr("tmp  ->  ");
	ft_putendl(tmp);
	if((directory = opendir(nextpwd)) == NULL)
	{
		ft_putendl_fd("OPENDIR ERROR", 1);
		return;
	}
	else
	{
		ft_putendl("Open Success");
		ft_setpwd(env, tmp, nextpwd);
		free(tmp);
		free(nextpwd);
	}

	dir = readdir(directory);
	ft_putendl(dir->d_name);
	// if (closedir(directory) != 0)
	// 	ft_putendl_fd("CLOSEDIR ERROR",2);
	(void)dir;
}

void		ft_setpwd(t_env **env, char *pwd, char *nextpwd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			ft_putstr("PWD ->>>>");
			ft_putendl(nextpwd);
			free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(nextpwd);
		}
		if (ft_strcmp(ptrmaillon->name, "OLDPWD") == 0)
		{
			ft_putstr("OLDPWD ->>>>");
			ft_putendl(pwd);
			free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(pwd);
		}
		ptrmaillon = ptrmaillon->next;
	}
}

// fd = open(ptrmaillon->value, O_RDONLY|O_DIRECTORY);
// if (fd == -1)
// {
// 	ft_putendl_fd("ERROR OPENDIR", 2); //Faire propre
// 	return;
// }


// if (fd == -1)
// 			{
// 				ft_putendl_fd("ERROR OPENDIR", 2); //Faire propre
// 				return;
// 			}