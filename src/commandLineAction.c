#include "minishell.h"

void			printPrompt(t_env *env)
{
	t_env		*ptrmaillon;
	char 		*value;

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
	ft_putstr("/$>  ");
	ft_putstr("\x1b[0m");
}



t_cmd			*initlcmd(void)
{
	t_cmd		*initmaillon;

	initmaillon = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(initmaillon))
		return (NULL);
	initmaillon->listcmd = NULL;
	initmaillon->next = NULL;
	return (initmaillon);
}


void			addlmaillon(char **cmd, t_cmd **liste)
{
	t_cmd		*newmaillon;
	t_cmd		*ptrmaillon;

	newmaillon = initlcmd();
	if (!(*liste))
		*liste = newmaillon;
	ptrmaillon = *liste;
	if (!(newmaillon) || !newmaillon)
		return ;
	while (ptrmaillon->next)
	{
		ptrmaillon = ptrmaillon->next;
	}
	ptrmaillon->next = newmaillon;
	newmaillon->listcmd = cmd;
	newmaillon->next = NULL;
}


void 			readCommandLine(t_cmd **base)
{
	char		*value;
	char		**cmd;
	int			ret;
	int 		i;

	i = 0;
	value = (char *)malloc(sizeof(char)*100000); //a modifier
	ret = read(STDIN_FILENO, value, 990000);
	if (ret == 0) // CHECK ThaT !!!!!!
	{
		ft_putendl("exit");
		free(value);
		exit(0);
	}
	value[ret - 1] = '\0';
	if (value)
	{
		cmd = ft_strsplit(value,';');
		while (cmd[i] != NULL)
		{
			addlmaillon(parseCmd(cmd[i]), base);
			i++;
		}
	}
}

char			**parseCmd(char *cmd)
{
	char		**cmdTab;
	int			i;
	int			j;
	int			k;

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

char			*malloc_tab(char *cmd, int pos)
{
	char		*cmdTab;
	int			len;

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

char			**setTab(char *cmd){
	char		**tab;
	int			size;
	int			i;

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
