#include "minishell.h"
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void	printPrompt(t_env *env)
{
	(void)env;
	t_env	*ptrmaillon;
	char 	*value;

	// ft_putendl("In PRompt");
	value = NULL;
	ptrmaillon = env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && (ft_strcmp(ptrmaillon->name, "USER") == 0)){
			if (ptrmaillon->value != NULL)
				value = ft_strdup(ptrmaillon->value);
			else
				value = NULL;
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (value)
	{
		ft_putstr("\x1b[31m");
		ft_putstr(value);
		free(value);
		ft_putstr("\x1b[0m");
	}
	ft_putstr("\x1b[32m");
	ft_putstr("/$>");
	ft_putstr("\x1b[0m");
}

char	**readCommandLine()
{
	char	*value;
	char	**cmd;
	int		ret;

	value = (char *)malloc(sizeof(char)*100);
	ret = read(STDIN_FILENO, value, 99);
	value[ret - 1] = '\0';
	if (value){
		cmd = parseCmd(value);	
		return (cmd);
	}
	return (NULL);
}

char		**parseCmd(char *cmd){
	char	**cmdTab;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	cmdTab = setTab(cmd);
	while (cmd[i] != '\0')
	{
		k = 0;
		while ((ft_isspace(cmd[i]) == 1) && cmd[i] != '\0')
			i++;
		if (cmd[i] != '\0')
			cmdTab[j] = malloc_tab(cmd, i);
		if (cmdTab[j] != NULL)
		{
			while ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0')
				cmdTab[j][k++] = cmd[i++];
			cmdTab[j][k] = '\0';
		}
		j++;
	}
	cmdTab[j] = NULL;
	return (cmdTab);
}

char		*malloc_tab(char *cmd, int pos){
	char	*cmdTab;
	int		len;

	len = 0;
	while ((ft_isspace(cmd[pos]) == 0) && cmd[pos] != '\0')
	{
		pos ++;
		len ++;
	}
	if (len != 0)
	{
		cmdTab = (char *)malloc(sizeof(char) * len);
		if (!cmdTab)
			return NULL;
	}
	else
		cmdTab = NULL;
	return (cmdTab);
}
char		**setTab(char *cmd){
	char	**tab;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (cmd[i] != '\0'){
		while ((ft_isspace(cmd[i]) == 1) && cmd[i] != '\0')
			i++;
		if ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0'){
			size++;
			while ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0')
				i++;
		}
	}
	tab = (char **)malloc(sizeof(char *)* size + 1);
	tab[size] = NULL;
	if (!tab)
		return (NULL);
	return (tab);
}
