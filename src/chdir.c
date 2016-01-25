#include "minishell.h"

void		ft_opendir(t_env **env, char **cmd){
	t_env			*ptrmaillon;
	DIR				*directory;
	char			*pwd;
	char			*tmp;
	char 			*nextpwd;

	ptrmaillon = *env;
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
	nextpwd = ft_strjoin(tmp, cmd[1]);
	free(pwd);
	// ft_putstr("nexpwd  ->  ");
	// ft_putendl(nextpwd);
	// ft_putstr("tmp  ->  ");
	// ft_putendl(tmp);
	if((directory = opendir(nextpwd)) == NULL)
	{
		ft_putendl_fd("OPENDIR ERROR", 1);
		free(tmp);
		free(nextpwd);
	}
	else
	{
		ft_putendl("Open Success");
		ft_setpwd(env, tmp, nextpwd);
		free(tmp);
		free(nextpwd);
	}
}

void		ft_setpwd(t_env **env, char *pwd, char *nextpwd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
		//	ft_putstr("PWD ->>>>");
		//	ft_putendl(nextpwd);
		//	free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(nextpwd);
		//	ft_putendl(ptrmaillon->value);
		}
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "OLDPWD") == 0)
		{
		//	ft_putstr("OLDPWD ->>>>");
		//	ft_putendl(pwd);
		//	free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(pwd);
		//	ft_putendl(ptrmaillon->value);
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