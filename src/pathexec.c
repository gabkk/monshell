#include "minishell.h"

char			*iscommande(t_env **env, char **cmd){
	char		*path;
	char		**tab_path;
	int			freepath;
	char		*value;

	freepath = 0;
	path = NULL;
	value = NULL;
	if (env) //peut etre non necessaire
		path = ft_getlistevalue(env, "PATH");
	tab_path = NULL;
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

char		*setpath(char **tab_path, char *cmd)
{
	DIR			*directory;
	t_dirent	content;
	int			i;
	char		*tmp;
	char 		*value;

	i = 0;
	value = NULL;
	while (tab_path[i] != NULL)
	{
		if ((directory = opendir(tab_path[i])) != NULL)
		{
			while ((content = readdir(directory)) != NULL)
			{
				if (cmd && ft_strcmp(content->d_name, cmd) == 0)
				{
					tmp = ft_strjoin("/", content->d_name);
					value = ft_strjoin(tab_path[i], tmp);
					free(tmp);
					closedir(directory);
					return (value);
				}
			}
			closedir(directory);
		}
		i++;
	}
	return (value);
}

char		*islocalexec(char **cmd){
	struct stat st;

	if (access(cmd[0], X_OK) == -1)
	{
		ft_putendl_fd("Acces non autorisé", 2);
		return (NULL);
	}
	if (lstat(cmd[0], &st) == 0 && st.st_mode & S_IXUSR)
		return (cmd[0]);
	return (NULL);
}
