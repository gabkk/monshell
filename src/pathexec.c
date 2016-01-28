#include "minishell.h"

char			*iscommande(t_env **env, char **cmd, char **pathtmp){
	char		*path;
	char		**tab_path;
	int			i;
	char		*value;


	i = 0;
	value = NULL;
	path = NULL;	
	if (env) //peut etre non necessaire
		path = ft_getlistevalue(env, "PATH");
	tab_path = NULL;
	tab_path = ft_strsplit(path, ':');
//	ft_ptab(tab_path);
	if (tab_path != NULL)
	{
		value = setpath(tab_path, value, cmd[0]);
		ft_freetab(tab_path);
	}
	else
	{
		//ft_putendl("inside pathtmp");
		//ft_ptab(pathtmp);
		value = setpath(pathtmp, value, cmd[0]);
	}

	//value = islocalexec(cmd); // verifier l'ordre
	return (value);
}

char		*setpath(char **tab_path, char *value, char *cmd)
{
	DIR			*directory;
	t_dirent	content;
	int			i;
	char		*tmp;

	i = 0;
	while (tab_path[i] != NULL)
	{
		if ((directory = opendir(tab_path[i])) != NULL)
		{
			while ((content = readdir(directory)) != NULL)
			{
				if (content && ft_strcmp(content->d_name, cmd) == 0)
				{
	//				ft_putendl(" inside setpath");
					tmp = ft_strjoin("/", content->d_name);
					value = ft_strjoin(tab_path[i], tmp);
	//				ft_putendl(value);

					free(tmp);
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

