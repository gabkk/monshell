#include "minishell.h"

void		addEnv(t_env **env, char **cmd)
{
	int		i;

	i = 0;
	if (!cmd[1])
		showenv(env);
	else if (ft_strcmp(cmd[1] ,"=") == 0 && !cmd[2])
		ft_putendl("You need to add a value and a parameter");
	else if (cmd[1] && !cmd[2])
	{
		while (cmd[1][i] != '\0')
		{
			if (cmd[1][i] == '=')
				return (setequal(env, cmd));
			i++;
		}
		setnoequal(env, cmd);
	}
	else if (cmd[1] && cmd[2])
	{
		if (setenv_twocmd(env, cmd) == 1)
			addNewEnv(env, cmd[1], cmd[2]);
	}
}

int			setenv_twocmd(t_env **env, char **cmd)
{
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
		{
			free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(cmd[2]);
			return (0);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (1);
}

void		setnoequal(t_env **env, char **cmd)
{
	t_env	*ptrmaillon;

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
	addNewEnv(env, cmd[1], cmd[2]);
}

void		setequal(t_env **env, char **cmd)
{
	t_env	*ptrmaillon;
	char	**varvalue;

	varvalue = NULL;
	if (*(varvalue = ft_strsplit(cmd[1], '=')) == NULL)
		return ((void)setequal_error());
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (*varvalue && ft_strcmp(ptrmaillon->name, varvalue[0]) == 0)
		{
			free(ptrmaillon->value);
			if (varvalue[1] != NULL)
				ptrmaillon->value = ft_strdup(varvalue[1]);
			else
				ptrmaillon->value = NULL;
			ft_freetab(varvalue);
			return ;
		}
		ptrmaillon = ptrmaillon->next;
	}
	addNewEnv(env, varvalue[0], varvalue[1]);
	ft_freetab(varvalue);
}

void		addNewEnv(t_env **env, char *cmd1, char *cmd2)
{
	t_env	*newmaillon;
	t_env	*ptrmaillon;

	newmaillon = initmaillon();
	ptrmaillon = *env;
	while (ptrmaillon->next)
		ptrmaillon = ptrmaillon->next;
	ptrmaillon->next = newmaillon;
	newmaillon->name = ft_strdup(cmd1);
	if (cmd2)
		newmaillon->value = ft_strdup(cmd2);
	else
		newmaillon->value = NULL;
}
