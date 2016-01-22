#include "minishell.h"

void		addEnv(t_env **env, char **cmd){
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	if (!cmd[1]){
		execenv(env);
		return;
	}
	if (ft_isupper(cmd[1]) == 0){
		ft_putendl("VAR should be set in capital");
		return;
	}
	if (cmd[1] && !cmd[2]){
		while (ptrmaillon){
			if (ft_strcmp(ptrmaillon->name, cmd[1]) == 0){
				invalidParam(cmd);
				return;
			}
			ptrmaillon = ptrmaillon->next;
		}
		addNewEnv(env, cmd);
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
