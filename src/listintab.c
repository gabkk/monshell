#include "minishell.h"

char 	**ft_listintab(t_env	**env){
	t_env	*ptrmaillon;
	char 	**tabenv;
	int 	i;
	int 	len;
	char	*tmp1;

	i = 0;
	len = 0;
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		i++;
		ptrmaillon = ptrmaillon->next;
	}
	tabenv = (char **)malloc(sizeof(char *) * i);
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
	return (tabenv);
}
