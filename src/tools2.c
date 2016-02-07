/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:45:06 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:45:08 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			env_new(t_env **env, char *cmd1, char *cmd2)
{
	t_env		*newmaillon;
	t_env		*ptrmaillon;

	newmaillon = initmaillon();
	ptrmaillon = *env;
	while (ptrmaillon->next)
		ptrmaillon = ptrmaillon->next;
	ptrmaillon->next = newmaillon;
	newmaillon->name = ft_strdup(cmd1);
	if (cmd2)
		newmaillon->value = ft_strdup(cmd2);
	else
		newmaillon->value = NULL;
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

void			sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_flagsignal != 0)
		{
			kill(g_flagsignal, SIGKILL);
			write(1, "\n", 1);
			g_flagsignal = 0;
		}
		return ;
	}
}
