#include "minishell.h"

char			*iscommande(t_env **env, char **cmd){
	char		*path;
	char		**tab_path;
	DIR			*directory;
	t_dirent	content;
	int			i;
	char		*tmp;
	char		*value;


	i = 0;
	value = NULL;
	path = ft_getlistevalue(env, "PATH");
	tab_path = ft_strsplit(path, ':');
	//ft_ptab(tab_path);
	while (tab_path[i] != NULL)
	{
		if((directory = opendir(tab_path[i])) == NULL)
			ft_putendl_fd("OPENDIR ERROR", 2);
		else
		{
			while ((content = readdir(directory)) != NULL)
			{
				if (content && ft_strcmp(content->d_name, cmd[0]) == 0)
				{
					tmp = ft_strjoin("/", content->d_name);
					value = ft_strjoin(tab_path[i], tmp);
					free(tmp);
					return (value);
				}
			}
		}
		i++;
	}
	value = islocalexec(cmd);
	return (value);
}

char		*islocalexec(char **cmd){
	struct stat st;

	if (access(cmd[0], X_OK) == -1)
	{
		ft_putendl("Access error");
		return (NULL);
	}
	if (lstat(cmd[0], &st) == 0 && st.st_mode & S_IXUSR) 
		return (cmd[0]);
	return (NULL);
}

