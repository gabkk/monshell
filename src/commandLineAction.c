#include "minishell.h"


void	printPrompt()
{
	ft_putstr("$>");
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