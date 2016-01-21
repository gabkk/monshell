#include "minishell.h"

void	getLocalEnv(char **env, t_env **liste){
	t_env	*newmaillon;
	int 	i;

	i = 2;
	if (!(env[i]))
		return;
	newmaillon = initEnv();
	*liste = fillEnv(newmaillon, env[i]);
	setLocalEnv(env, i, liste);
	return ;
}

void	setLocalEnv(char **env, int i, t_env **liste){
	t_env	*newmaillon;
	t_env	*ptrmaillon;

	while (env[i] != NULL)
	{
		newmaillon = initEnv();
		if (!(*liste))
			*liste = newmaillon;
		ptrmaillon = *liste;
		while (ptrmaillon->next){
			ptrmaillon = ptrmaillon->next;
		}
		ptrmaillon->next = newmaillon;
		newmaillon = fillEnv(newmaillon, env[i]);
		newmaillon->next = NULL;
		i++;
	}
}

t_env *fillEnv(t_env *newmaillon, char *fullEnv){
	int i;
	int ptr;
	int equal;
	int len;
	char *name;
	char *value;

	i = 0;
	ptr = 0;
	equal = 0;
	len = ft_strlen(fullEnv);
	name = (char*)malloc(sizeof(char)*len);
	value = (char*)malloc(sizeof(char)*len);
	while (fullEnv[i] != '\0')
	{
		if (equal == 0)
		{
			if (fullEnv[i] != '='){
				name[ptr] = fullEnv[i];
			}
			else{
				equal = 1;
				name[ptr] = '\0';
				ptr = -1;
			}
		}else{
			value[ptr] = fullEnv[i];
		}
		ptr++;
		i++;
	}
	value[ptr] = '\0';
	newmaillon->name = ft_strdup(name);
	newmaillon->value = ft_strdup(value);
	free(name);
	free(value);
	return (newmaillon);
}

t_env	*initEnv(void){
	t_env	*initmaillon;

	initmaillon = (t_env *)malloc(sizeof(t_env));
	if (!(initmaillon))
		return (NULL);
	initmaillon->name = NULL;
	initmaillon->value = NULL;
	initmaillon->next = NULL;
	return (initmaillon);
}
