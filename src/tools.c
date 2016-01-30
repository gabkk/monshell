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

	pathtmp = (char **)malloc(sizeof(char *) * 2);
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
	defaultenv[0] = "HOSTTYPE=unknown";
	defaultenv[1] = "VENDOR=apple";
	defaultenv[2] = "OSTYPE=darwin";
	defaultenv[3] = "MACHTYPE=x86_64";
	defaultenv[4] = "SHLVL=1";
	defaultenv[5] = ft_strjoin("PWD=", getcwd(tmp, PATH_MAX));
	defaultenv[6] = "LOGNAME=default";
	defaultenv[7] = "USER=default";
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

void		setshlvl(char **tabenv)
{
	char	**tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;
	int		value;

	i = 0 ;
	while (tabenv[i] != NULL)
	{
		if (ft_strncmp(tabenv[i], "SHLVL", 5) == 0)
		{
			tmp = ft_strsplit(tabenv[i], '=');
			if (tmp[1])
			{
				value = ft_atoi(tmp[1]) + 1;
				tmp3 = ft_itoa(value);	
			}		
			tmp2 = ft_strjoin(tmp[0], "=");
			tabenv[i] = ft_strjoin(tmp2, tmp3);
			ft_freetab(tmp);
			free(tmp2);
			free(tmp3);
		}
		i++;
	}
}

void		setlistlvl(t_env **env)
{
	t_env	*ptrmaillon;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "SHLVL") == 0)
			ptrmaillon->value = ft_itoa(ft_atoi(ptrmaillon->value) + 1); // a free
		ptrmaillon = ptrmaillon->next;
	}
}
