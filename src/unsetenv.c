#include "minishell.h"

void		unset_env(t_env **env, char **cmd){
	t_env	*ptrmaillon;
	t_env	*prevmaillon;

	ptrmaillon = *env;
	if (ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
	{
		*env = ptrmaillon->next;
		free(ptrmaillon);
		unset_env(env, cmd);
		return;
	}
	while (ptrmaillon->next != NULL)
	{
		if (ft_strcmp(ptrmaillon->next->name, cmd[1]) == 0)
		{
			prevmaillon = ptrmaillon->next;
			ptrmaillon->next = prevmaillon->next;
			free(prevmaillon);
		}
		else
			ptrmaillon = ptrmaillon->next;
	}	
}
