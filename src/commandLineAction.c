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
				value = ptrmaillon->value;
			else
				value = NULL;
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (value)
	{
		ft_putstr("\x1b[31m");
		ft_putstr(value);
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
	value = NULL;
	value = (char *)malloc(sizeof(char)* 1026);
	ret = read(STDIN_FILENO, value, 1025);
	if (ret == 0)
	{
		ft_putendl("exit");
		free(value);
		exit(0);
	}
	if ((checkifonlyspace(value) == 1))
		return;
	value[ret - 1] = '\0';
	ft_putstr("value retour de ret: |");
	ft_putstr(value);
	ft_putendl("|");
	if (*value)
	{
		cmd = ft_strsplit(value,';');
		while (cmd[i] != NULL)
		{
//			ft_putendl(cmd[i]);
			addlmaillon(parseCmd(cmd[i]), base);
			free(cmd[i]);
			i++;
		}
		free(cmd[i]);
		free(cmd);
	}
	free(value);
}

char			**parseCmd(char *cmdvalue)
{
	char		**cmdTab;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	cmdTab = setTab(cmdvalue);
	while (cmdvalue[i] != '\0')
	{
		k = 0;
		while ((cmdvalue[i] != '\0' && ft_isspace(cmdvalue[i]) == 1))
			i++;
		if (cmdvalue[i] != '\0')
			cmdTab[j] = malloc_tab(cmdvalue, i);

		if (cmdTab[j] != NULL)
		{
			while (cmdvalue[i] != '\0' && (ft_isspace(cmdvalue[i]) == 0))
				cmdTab[j][k++] = cmdvalue[i++];
			cmdTab[j][k] = '\0';
		}
		while ((cmdvalue[i] != '\0' && ft_isspace(cmdvalue[i]) == 1))
			i++;
		ft_putstr("commande parse: |");
		ft_putstr(cmdTab[j]);
		ft_putendl("|");
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
	while (cmd[pos] != '\0' && (ft_isspace(cmd[pos]) == 0))
	{
		pos ++;
		len ++;
	}
	if (len != 0)
	{
		// ft_putstr("len -->  ");
		// ft_putnbr(len + 1);
		cmdTab = (char *)malloc(sizeof(char) * len + 1);
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
		while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 1))
			i++;
		if (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 0))
		{
			size++;
			while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 0))
				i++;
		}
	}
	ft_putstr("size -->");
	ft_putnbr(size + 1);
	ft_putendl("");
	tab = (char **)malloc(sizeof(char *)* (size + 1));
	if (!tab)
		return (NULL);
	return (tab);
}
