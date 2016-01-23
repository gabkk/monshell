#include "minishell.h"

void		addEnv(t_env **env, char **cmd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	if (!cmd[1]){
		showenv(env);
		return;
	}
	if (isvalidvar(cmd[1]) == 0){
		return;
	}
	if (cmd[1] && !cmd[2]){
		ft_putendl("step 1");
		if(withequal(cmd[1]) == 0)
			setnoequal(env, cmd);
		else
			setequal(env, cmd);
	} else if (cmd[1] && cmd[2]){
		while (ptrmaillon){
			if (ft_strcmp(ptrmaillon->name, cmd[1]) == 0){
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

	ft_putstr("no equal");
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
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

	(void)env;
	ft_putstr("equal");
	varvalue = ft_strsplit(cmd[1], '=');

	//ft_putendl(varvalue[0]);
	//ft_putendl(varvalue[1]);
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, varvalue[0]) == 0)
		{
			if (varvalue[1] != NULL)
				ptrmaillon->value = varvalue[1];
			else
				ptrmaillon->value = NULL;
			return;
		}
		ptrmaillon = ptrmaillon->next;
	}
	cmd[1] = varvalue[0];
	if (varvalue[1] != NULL)
		cmd[2] = varvalue[1];
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

	newmaillon = initEnv();
	ptrmaillon = *env;
	while (ptrmaillon->next){
		ptrmaillon = ptrmaillon->next;
	}
	ptrmaillon->next = newmaillon;
	newmaillon->name = cmd[1];
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
		if (str[i] == '=')
		{
			if (str[i] == '=' && ft_strlen(str) == 1)
			{
				ft_putendl("You need to add a value and a parameter");
				return (0);
			}
			valid++;
			if (valid > 1)
			{
				ft_putendl("Parameter of setenv can't have more than one =");
				return (0);
			}
		}
		if ((str[i] < 65 || str[i] > 90) && str[i] != '=')
		{
			if (valid == 1)
				return (1);
			ft_putendl("VAR should be set in capital");
			return (0);
		}
		i++;
	}
	return (1);
}