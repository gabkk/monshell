/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:42:11 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:42:12 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*iscommande(t_env **env, char **cmd)
{
	char		*path;
	char		**tab_path;
	int			freepath;
	char		*value;

	freepath = 0;
	path = NULL;
	value = NULL;
	tab_path = NULL;
	path = getlistevalue(env, "PATH");
	if (path)
		tab_path = ft_strsplit(path, ':');
	else
	{
		tab_path = setdefaultpath();
		freepath = 1;
	}
	value = setpath(tab_path, cmd[0]);
	if (freepath == 0)
		ft_freetab(tab_path);
	else if (freepath == 1)
		free(tab_path);
	return (value);
}

char			*setpath(char **tab_path, char *cmd)
{
	DIR			*directory;
	char		*value;
	int			i;

	i = 0;
	value = NULL;
	while (tab_path[i] != NULL)
	{
		if ((directory = opendir(tab_path[i])) != NULL)
		{
			if ((value = path_fill(directory, cmd, tab_path[i])) != NULL)
				return (value);
			closedir(directory);
		}
		i++;
	}
	return (value);
}

char			*path_fill(DIR *directory, char *cmd, char *tab_path)
{
	t_dirent	content;
	char		*tmp;
	char		*value;

	value = NULL;
	while ((content = readdir(directory)) != NULL)
	{
		if (cmd && ft_strcmp(content->d_name, cmd) == 0)
		{
			tmp = ft_strjoin("/", content->d_name);
			value = ft_strjoin(tab_path, tmp);
			free(tmp);
			closedir(directory);
			return (value);
		}
	}
	return (value);
}

int				islocalexec(char *cmd)
{
	DIR			*directory;
	t_dirent	content;
	

	if ((directory = opendir(".")) != NULL)
	{
		while ((content = readdir(directory)) != NULL)
		{
			if (cmd && ft_strcmp(content->d_name, cmd) == 0)
				return (1);
		}
	}
	return (0);
}

char		**setdefaultpath(void)
{
	char	**pathtmp;

	pathtmp = (char **)malloc(sizeof(char *) * 3);
	pathtmp[0] = "/bin";
	pathtmp[1] = "/usr/bin";
	pathtmp[2] = NULL;
	return (pathtmp);
}