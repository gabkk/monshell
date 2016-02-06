#include "minishell.h"

void			printPrompt(t_env *env)
{
	t_env		*ptrmaillon;
	char		*value;

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

	if (!(*cmd))
		return ;
	newmaillon = initlcmd();
	if (!(*liste))
	{
		*liste = newmaillon;
		newmaillon->listcmd = cmd;
		newmaillon->next = NULL;
		return;
	}
	ptrmaillon = *liste;
	while (ptrmaillon->next)
		ptrmaillon = ptrmaillon->next;
	ptrmaillon->next = newmaillon;
	newmaillon->listcmd = cmd;
	newmaillon->next = NULL;
}


void 			readCommandLine(t_cmd **base)
{
	char		*value;
	int			ret;
	char		**tmp;

	value = NULL;
	tmp = NULL;
	value = (char *)malloc(sizeof(char)* 1026);
	ret = read(STDIN_FILENO, value, 1025);
	if (ret == 0)
	{
		ft_putendl("exit");
		free(value);
		exit(0);
	}
	value[ret - 1] = '\0';
	parse_value(value, tmp, base);
}

void			parse_value(char *value, char **tmp, t_cmd **base)
{
	int 		i;
	char		**cmd;

	i = 0;
	if ((checkifonlyspace(value) == 1))
	{
		free(value);
		return;
	}
	if (*value)
	{
		cmd = ft_strsplit(value,';');
		if (!*cmd)
			return ;
		while (cmd[i])
		{
			tmp = parseCmd(cmd[i]);
			if (tmp)
				addlmaillon(tmp, base);
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
	if (!(*cmdvalue))
		return NULL;
	cmdTab = setTab(cmdvalue);
	if (!cmdTab)
		return NULL;
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
		cmdTab = (char *)malloc(sizeof (char) * len + 1);
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
	tab = NULL;
	while (cmd[i] != '\0')
	{
		while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 1))
			i++;
		if (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 0))
		{
			size++;
			while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 0))
				i++;
		}
		while (cmd[i] != '\0' && (ft_isspace(cmd[i]) == 1))
			i++;
	}
	if (size != 0)
		tab = (char **)malloc(sizeof (char *) * (size + 1));
	if (!tab)
		return (NULL);
	return (tab);
}
