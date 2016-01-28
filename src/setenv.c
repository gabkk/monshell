#include "minishell.h"

void		addEnv(t_env **env, char **cmd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	if (!cmd[1])
	{
		//ft_putendl("!cmd1");
		showenv(env);
		return;
	}
	// ft_putendl("2");
	if (isvalidvar(cmd[1]) == 0)
	{
		return;
	}
	// ft_putendl("3");
	if (!cmd[1] && !cmd[2])
	{
		ft_putendl("Please enter at least 1 VAR");
		return;
	}
	if (cmd[1] && !cmd[2])
	{ 
		if(withequal(cmd[1]) == 0)
			setnoequal(env, cmd);
		else
			setequal(env, cmd);
	}
	else if (cmd[1] && cmd[2])
	{
		// ft_putendl("2 parameter");
		// ft_putendl(ptrmaillon->name);
		if (ft_isupper(cmd[1]) == 0){
			ft_putendl("VAR should contain only capital letter");
			return;
		}
		while (ptrmaillon)
		{
			if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
			{
				ptrmaillon->value = cmd[2];
				return;
			}
			ptrmaillon = ptrmaillon->next;
		}
		addNewEnv(env, cmd);
	}
}

void		setnoequal(t_env **env, char **cmd){
	t_env	*ptrmaillon;

	// ft_putendl("noequal");
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
		{
			setenvError(cmd);
			return;
		}
		ptrmaillon = ptrmaillon->next;
	}
	addNewEnv(env, cmd);
}

void		setequal(t_env **env, char **cmd){
	t_env	*ptrmaillon;
	char 	**varvalue;

	// ft_putendl("equal");
	varvalue = ft_strsplit(cmd[1], '=');
	ptrmaillon = *env;
	// ft_putendl(ptrmaillon->name);
	// ft_putendl("equal 1");
	while (ptrmaillon)
	{
//		ft_putendl(ptrmaillon->name);
		if ((ptrmaillon->name) && ft_strcmp(ptrmaillon->name, varvalue[0]) == 0)
		{
			if (varvalue[1] != NULL)
				ptrmaillon->value = varvalue[1];
			else
				ptrmaillon->value = NULL;
			return;
		}
		ptrmaillon = ptrmaillon->next;
	}
	// ft_putendl("equal 2");
	cmd[1] = varvalue[0];
	if (varvalue[1] != NULL)
		cmd[2] = varvalue[1];
	// ft_putendl("equal 3");
	addNewEnv(env, cmd);
}

int 		withequal(char *str){
	int 	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void		addNewEnv(t_env **env, char **cmd){
	t_env	*newmaillon;
	t_env	*ptrmaillon;

	// ft_putendl("inside addNEWenv");
	newmaillon = initmaillon();
	ptrmaillon = *env;
	while (ptrmaillon->next){
		ptrmaillon = ptrmaillon->next;
	}
	ptrmaillon->next = newmaillon;
	newmaillon->name = cmd[1];
//	ft_putendl(newmaillon->name);
	if (cmd[2])
		newmaillon->value = cmd[2];
}


int			isvalidvar(char *str){
	int		i;
	int		valid;

	i = 0;
	valid = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=' || str[i] == '_')
		{
			if (str[i] == '=')
				valid++;
			if (str[i] == '=' && ft_strlen(str) == 1)
			{
				ft_putendl("You need to add a value and a parameter");
				return (0);
			}
			if (valid > 1)
			{
				ft_putendl("Parameter of setenv can't have more than one =");
				return (0);
			}
		}
		else if (str[i] < 65 || str[i] > 90)
		{
			if (valid == 1)
				return (1);
			ft_putendl("VAR should contain only capital letter");
			return (0);
		}
		i++;
	}
	return (1);
}