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
	return (value);
}