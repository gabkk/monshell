#include "minishell.h"

void		unset_env(t_env **env, char **cmd){
	t_env	*ptrmaillon;
	t_env	*prevmaillon;

	if (!(*env)){
		ft_putstr("ENV NUL");
		return;
	}
	ptrmaillon = *env;
	//  ft_putstr("ptr - >");
	//  ft_putendl(ptrmaillon->name);
	//  ft_putstr("cmd[1] - >");
	//  ft_putendl(cmd[1]);
	//  ft_putstr("next - >");
	//  ft_putendl(ptrmaillon->next->name);
	 if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, cmd[1]) == 0)
	{
	//	ft_putendl("DEL");
		*env = ptrmaillon->next;
		ptrmaillon->name = NULL;
		ptrmaillon->value = NULL;
		free(ptrmaillon);
		unset_env(env, cmd);
		return;
	}
	while (ptrmaillon->next != NULL)
	{
		if ((ptrmaillon->next->name) && ft_strcmp(ptrmaillon->next->name, cmd[1]) == 0)
		{
			//ft_putendl(ptrmaillon->next->name);
			prevmaillon = ptrmaillon->next;
			ptrmaillon->next = prevmaillon->next;
			free(prevmaillon);
		}
		else
			ptrmaillon = ptrmaillon->next;
	}	
}
