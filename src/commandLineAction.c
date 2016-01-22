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
		return(cmd);
	}
	return (NULL);
}

char		**parseCmd(char *cmd){
	char	**cmdTab;
	int		i;
	int		j;
	int		k;
	int		len;
	int 	pos;

	i = 0;
	j = 0;
	cmdTab = setTab(cmd);
	while (cmd[i] != '\0')
	{
		len = 0;
		k = 0;
		while ((ft_isspace(cmd[i]) == 1) && cmd[i] != '\0')
			i++;
		pos = i;
		while ((ft_isspace(cmd[pos]) == 0) && cmd[pos] != '\0')
		{
			pos ++;
			len ++;
		}
		cmdTab[j] = (char *)malloc(sizeof(char) * len);
		while ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0')
		{
			cmdTab[j][k] = cmd[i];
			i++;
			k++;
		}
		cmdTab[j][k] = '\0';
		j++;
	}
	return (cmdTab);
}

char		**setTab(char *cmd){
	char	**tab;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (cmd[i] != '\0'){
		while ((ft_isspace(cmd[i]) == 1))
			i++;
		if ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0'){
			size++;
			while ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0')
				i++;
		}
	}
	tab = (char **)malloc(sizeof(char *)* size);
	tab[size] = NULL
	return (tab);
}
