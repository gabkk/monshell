/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:44:48 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:44:52 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_getlistevalue(t_env **env, char *name)
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

char		**setdefaultpath(void)
{
	char	**pathtmp;

	pathtmp = (char **)malloc(sizeof(char *) * 3);
	pathtmp[0] = "/bin";
	pathtmp[1] = "/usr/bin";
	pathtmp[2] = NULL;
	return (pathtmp);
}

char		**getdefaultenv(void)
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

t_env		*setdefaultenv(void)
{
	t_env	*liste;
	char	**defaultenv;
	char	**tmp;
	int		i;

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

void		ft_listintab(t_env **env, char **tabenv)
{
	int		i;
	char	*tmp1;
	t_env	*ptrmaillon;

	i = 0;
	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name)
		{
			tmp1 = ft_strjoin(ptrmaillon->name, "=");
			if (ptrmaillon->value)
				tabenv[i] = ft_strjoin(tmp1, ptrmaillon->value);
			else
				tabenv[i] = ft_strdup(tmp1);
			free(tmp1);
			i++;
		}
		ptrmaillon = ptrmaillon->next;
	}
	tabenv[i] = NULL;
}
