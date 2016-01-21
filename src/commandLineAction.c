#include "minishell.h"


void	printPrompt(t_env **env)
{
	t_env	*ptrmaillon;
	char 	*name;

	name = NULL;
	ptrmaillon = *env;
	while (ptrmaillon->next)
	{
		if (ft_strcmp(ptrmaillon->name, "USER") == 0){
			name = ft_strdup(ptrmaillon->value);
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (name != NULL)
		ft_putstr(name);
	ft_putstr("/$>");
	free(name);
}

char	*readCommandLine()
{
	int		ret;
	char	*value;

	value = malloc(sizeof(char)*100);
	ret = read(1, value, 99);
	value[ret - 1] = '\0';
	return(value);
}