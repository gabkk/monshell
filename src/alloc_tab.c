# include "minishell.h"

char			**parse_cmd(char *cmdvalue)
{
	char		**cmdTab;

	if (!(*cmdvalue))
		return NULL;
	cmdTab = setTab(cmdvalue);
	if (!cmdTab)
		return NULL;
	fill_cmd_tab(cmdvalue, cmdTab);
	return (cmdTab);
}

void			fill_cmd_tab(char *cmdvalue,char **cmdTab)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
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
