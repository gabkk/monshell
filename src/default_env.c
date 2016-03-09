/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:44:48 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:44:52 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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