#include "minishell.h"

char		*ft_getlistevalue(t_env	**env, char *name)
{
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, name) == 0)
		{
			tmp = ptrmaillon->value;
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}

char		**setdefaultpath()
{
	char	**pathtmp;

	pathtmp = (char **)malloc(sizeof(char *) * 3);
	pathtmp[0] = "/bin";
	pathtmp[1] = "/usr/bin";
	pathtmp[2] = NULL;
	return (pathtmp);
}

char		**getdefaultenv()
{
	char	**defaultenv;
	char	tmp[PATH_MAX];

	defaultenv = (char **)malloc(sizeof(char *) * 9);
	defaultenv[0] = ft_strdup("HOSTTYPE=unknown");
	defaultenv[1] = ft_strdup("VENDOR=apple");
	defaultenv[2] = ft_strdup("OSTYPE=darwin");
	defaultenv[3] = ft_strdup("MACHTYPE=x86_64");
	defaultenv[4] = ft_strdup("SHLVL=1");
	defaultenv[5] = ft_strjoin("PWD=", getcwd(tmp, PATH_MAX));
	defaultenv[6] = ft_strdup("LOGNAME=default");
	defaultenv[7] = ft_strdup("USER=default");
	defaultenv[8] = NULL;
	return (defaultenv);
}

t_env		*setdefaultenv()
{
	t_env	*liste;
	char	**defaultenv;
	char	**tmp;
	int 	i;

	i = 0;
	defaultenv = getdefaultenv();
	liste = NULL;
	while (defaultenv[i] != NULL)
	{
		tmp = ft_strsplit(defaultenv[i], '=');
		addmaillon(tmp[0], tmp[1], &liste);
		ft_freetab(tmp);
		i++;
	}
	free(defaultenv[5]);
	free(defaultenv);
	return (liste);
}


void		setlistlvl(t_env **env)
{
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "SHLVL") == 0)
		{
			free(ptrmaillon->value);
			ptrmaillon->value = ft_itoa(ft_atoi(ptrmaillon->value) + 1); // a free
		}
		ptrmaillon = ptrmaillon->next;
	}
}

int			checkifonlyspace(char *value)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (ft_isspace(value[i]))
			j++;
		i++;
	}
	if (i == j)
		return(1);
	return 0;
}

// void		setshlvl(char **tabenv)
// {
// 	char	**tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	int		i;
// 	int		value;

// 	i = 0 ;
// 			ft_putstr("start");

// 	while (tabenv[i] != NULL)
// 	{
// 			ft_putstr("start");
	
// 		if (ft_strncmp(tabenv[i], "SHLVL", 5) == 0)
// 		{
// 			ft_putstr("start");
	
// 			tmp = ft_strsplit(tabenv[i], '=');
// 			if (tmp[1])
// 			{
// 				value = ft_atoi(tmp[1]) + 1;
// 				tmp3 = ft_itoa(value);	
// 			}		
// 			tmp2 = ft_strjoin(tmp[0], "=");
// 			ft_putstr("start");
// 			ft_putendl(tabenv[i]); //del
// 			free(tabenv[i]);
// 			tabenv[i] = ft_strjoin(tmp2, tmp3);
// 			ft_freetab(tmp);
// 			free(tmp2);
// 			free(tmp3);
// 		}
// 		i++;
// 	}
// }
