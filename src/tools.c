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

char		*getlistevalue(t_env **env, char *name)
{
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, name) == 0)
		{
			tmp = ptrmaillon->value;
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}

int				checkifonlyspace(char *value)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (ft_isspace(value[i]) == 1)
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

void			setlistlvl(t_env **env)
{
	t_env		*ptrmaillon;
	char		*tmp;
	int			i;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "SHLVL") == 0)
		{
			i = ft_atoi(ptrmaillon->value) + 1;
			tmp = ft_itoa(i);
			free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(tmp);
			free(tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
}

void		randcol_ansi(int i)
{
	char	*tmp1;
	char	*tmp2;
	char	*nbr;

	nbr = ft_itoa(i);
	tmp1 = ft_strjoin(nbr, "m");
	tmp2 = ft_strjoin("\x1b[38;5;", tmp1);
	ft_putstr(tmp2);
	free(nbr);
	free(tmp1);
	free(tmp2);
}
