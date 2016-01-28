#include "minishell.h"

char		*ft_getlistevalue(t_env	**env, char *name){
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, name) == 0)
		{
			tmp = ptrmaillon->value;
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}