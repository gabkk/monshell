/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:47:16 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:47:17 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				unset_env(t_env **env, char **cmd)
{
	t_env			*ptm;
	t_env			*prevmaillon;
	int				i;

	i = 0;
	prevmaillon = NULL;
	if (!(*env) || !cmd[1])
		return ;
	while (cmd[i] != NULL)
	{
		ptm = *env;
		if (ptm->name && ft_strcmp(ptm->name, cmd[i]) == 0)
		{
			*env = ptm->next;
			free(ptm->name);
			free(ptm->value);
			ptm->value = NULL;
			free(ptm);
			unset_env(env, cmd);
			return ;
		}
		unset_env_first(ptm, prevmaillon, cmd[i]);
		i++;
	}
}

void				unset_env_first(t_env *ptm, t_env *prev, char *cmd)
{
	while (ptm->next != NULL)
	{
		if ((ptm->next->name) && ft_strcmp(ptm->next->name, cmd) == 0)
		{
			prev = ptm->next;
			ptm->next = prev->next;
			free(prev->value);
			free(prev->name);
			free(prev);
		}
		else
			ptm = ptm->next;
	}
}

void				freebase(t_cmd **base)
{
	t_cmd			*ptrmaillon;

	if (!base || !*base)
		return ;
	while (*base)
	{
		if ((*base)->listcmd)
			ft_freetab((*base)->listcmd);
		ptrmaillon = (*base)->next;
		free(*base);
		*base = ptrmaillon;
	}
	*base = NULL;
}

void				freenv(t_env *env)
{
	t_env			*ptrmaillon;

	while (env != NULL)
	{
		free(env->name);
		if (env->value)
			free(env->value);
		ptrmaillon = env;
		free(env);
		env = ptrmaillon->next;
	}
}
