#include "minishell.h"

void		ft_listintab(t_env	**env, char **tabenv)
{
	int 	i;
	char	*tmp1;
	t_env	*ptrmaillon;

	i = 0;
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name)
		{
			tmp1 = ft_strjoin(ptrmaillon->name, "=");
			if (ptrmaillon->value)
				tabenv[i] = ft_strjoin(tmp1, ptrmaillon->value);
			else
				tabenv[i] = ft_strdup(tmp1);
			free(tmp1);
			i++;
		}
		ptrmaillon = ptrmaillon->next;
	}
	tabenv[i] = NULL;
}
