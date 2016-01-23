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
			if (ptrmaillon->value != NULL)
				value = ft_strdup(ptrmaillon->value);
			else
				value = ft_strdup(" ");
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
	int		pos;

	i = 0;
	j = 0;
	pos = 0;
	cmdTab = setTab(cmd);
	while (cmd[i] != '\0')
	{
		len = 0;
		k = 0;
//	ft_putendl("a");
		while ((ft_isspace(cmd[i]) == 1) && cmd[i] != '\0')
			i++;
		pos = i;
//	ft_putendl("b");
		while ((ft_isspace(cmd[pos]) == 0) && cmd[pos] != '\0')
		{
			pos ++;
			len ++;
		}
//		ft_putnbr(len);
	ft_putendl("len");
		if (len != 0)
		{
			cmdTab[j] = (char *)malloc(sizeof(char) * len);
			if (!cmdTab[j])
				return NULL;
		}
//	ft_putendl("d");
		while ((ft_isspace(cmd[i]) == 0) && cmd[i] != '\0')
		{
			cmdTab[j][k] = cmd[i];
			i++;
			k++;
		}
//	ft_putendl("e");
		if (len != 0)
			cmdTab[j][k] = '\0';
		ft_putnbr(j);
		ft_putendl(cmdTab[j]);
		j++;
	}
//	ft_putendl("end");
	ft_putnbr(j);
	cmdTab[j] = NULL;
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
//	ft_putnbr(size);
	tab = (char **)malloc(sizeof(char *)* size + 1);
	if (!tab)
		return(NULL);
	return (tab);
}
