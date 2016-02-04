#include "minishell.h"

void		unset_env(t_env **env, char **cmd){
	t_env	*ptrmaillon;
	t_env	*prevmaillon;
	int		i;

	i = 0;
	if (!(*env) || !cmd[1])
		return;
	while (cmd[i] != NULL)
	{
		ptrmaillon = *env;
		 if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, cmd[i]) == 0)
		{
			*env = ptrmaillon->next;
			free(ptrmaillon->name);
			free(ptrmaillon->value);
			ptrmaillon->value = NULL;
			free(ptrmaillon);
			unset_env(env, cmd);

			return;
		}
		while (ptrmaillon->next != NULL)
		{
			if ((ptrmaillon->next->name) && ft_strcmp(ptrmaillon->next->name, cmd[i]) == 0)
			{
				prevmaillon = ptrmaillon->next;
				ptrmaillon->next = prevmaillon->next;
				free(prevmaillon->value);
				free(prevmaillon->name);
				free(prevmaillon);
			}
			else
				ptrmaillon = ptrmaillon->next;
		}
	i++;
	}
}
