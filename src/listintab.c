#include "minishell.h"

void		ft_listintab(t_env	**env, char **tabenv)
{
	int 	i;
	int 	len;
	char	*tmp1;
	t_env	*ptrmaillon;

	len = 0;
	ptrmaillon = *env;
	i = 0;
	while (ptrmaillon)
	{
		if (ptrmaillon->name)
		{
			len = ft_strlen(ptrmaillon->name);
			if (ptrmaillon->value)
				len += ft_strlen(ptrmaillon->value);
			tabenv[i] = malloc(sizeof(char) * (len + 2));
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
