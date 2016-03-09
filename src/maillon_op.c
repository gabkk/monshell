/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maillon_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:33:17 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:33:19 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env			*initmaillon(void)
{
	t_env		*newmaillon;

	newmaillon = (t_env *)malloc(sizeof(t_env));
	if (!(newmaillon))
		return (NULL);
	newmaillon->name = NULL;
	newmaillon->value = NULL;
	newmaillon->next = NULL;
	return (newmaillon);
}

void			addmaillon(char *name, char *value, t_env **liste)
{
	t_env		*newmaillon;
	t_env		*ptrmaillon;

	newmaillon = initmaillon();
	if (!(*liste))
		*liste = newmaillon;
	ptrmaillon = *liste;
	if (!(newmaillon) || !newmaillon)
		return ;
	while (ptrmaillon->next)
	{
		ptrmaillon = ptrmaillon->next;
	}
	ptrmaillon->next = newmaillon;
	newmaillon->name = ft_strdup(name);
	newmaillon->value = ft_strdup(value);
	newmaillon->next = NULL;
}

void			setenv_maillon(char *pwd, char *nextpwd, t_env *ptm)
{
	char		*tmp2;

	if (ptm->name && ft_strcmp(ptm->name, "PWD") == 0)
	{
		if (nextpwd)
		{
			if (ptm->value)
				free(ptm->value);
			tmp2 = (char *)malloc(sizeof(char) * PATH_MAX + 1);
			if (getcwd(tmp2, PATH_MAX) != NULL)
				ptm->value = ft_strdup(tmp2);
			free(tmp2);
		}
	}
	if (ptm->name && ft_strcmp(ptm->name, "OLDPWD") == 0)
	{
		if (pwd)
		{
			if (ptm->value)
				free(ptm->value);
			ptm->value = ft_strdup(pwd);
		}
	}
}

void			add_maillon_cmd(char **cmd, t_cmd **liste)
{
	t_cmd		*newmaillon;
	t_cmd		*ptrmaillon;

	if (!(*cmd))
		return ;
	newmaillon = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(newmaillon))
		return ;
	newmaillon->listcmd = NULL;
	newmaillon->next = NULL;
	if (!(*liste))
	{
		*liste = newmaillon;
		newmaillon->listcmd = cmd;
		newmaillon->next = NULL;
		return ;
	}
	ptrmaillon = *liste;
	while (ptrmaillon->next)
		ptrmaillon = ptrmaillon->next;
	ptrmaillon->next = newmaillon;
	newmaillon->listcmd = cmd;
	newmaillon->next = NULL;
}
