#include "minishell.h"


void	printPrompt(t_env *env)
{
	t_env	*ptrmaillon;
	char 	*value;

	value = NULL;
	ptrmaillon = env;
	while (ptrmaillon != NULL)
	{
		if ((ft_strcmp(ptrmaillon->name, "USER") == 0)){
			value = ft_strdup(ptrmaillon->value);
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (value)
		ft_putstr(value);
	ft_putstr("/$>");
	free(value);
}

char	*readCommandLine()
{
	int		ret;
	char	*value;

	value = malloc(sizeof(char)*100);
	ret = read(STDIN_FILENO, value, 99);
	value[ret - 1] = '\0';
	return(value);
}