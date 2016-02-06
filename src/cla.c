#include "minishell.h"

void			addlmaillon(char **cmd, t_cmd **liste)
{
	t_cmd		*newmaillon;
	t_cmd		*ptrmaillon;

	if (!(*cmd))
		return ;
	newmaillon = (t_cmd *)malloc(sizeof (t_cmd));
	if (!(newmaillon))
		return ;
	newmaillon->listcmd = NULL;
	newmaillon->next = NULL;
	if (!(*liste))
	{
		*liste = newmaillon;
		newmaillon->listcmd = cmd;
		newmaillon->next = NULL;
		return ;
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
	value = (char *)malloc(sizeof (char)* 1026);
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
		return ;
	}
	if (*value)
	{
		cmd = ft_strsplit(value,';');
		if (!*cmd)
			return ;
		while (cmd[i])
		{
			tmp = parse_cmd(cmd[i]);
			if (tmp)
				addlmaillon(tmp, base);
			free(cmd[i]);
			i++;
		}
		//free(cmd[i]);
		free(cmd);
	}
	free(value);
}
