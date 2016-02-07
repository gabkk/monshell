/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:40:10 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:40:11 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_prompt(t_env *env)
{
	t_env		*ptrmaillon;
	char		*value;

	value = NULL;
	ptrmaillon = env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && (ft_strcmp(ptrmaillon->name, "USER") == 0))
		{
			if (ptrmaillon->value != NULL)
				value = ptrmaillon->value;
			else
				value = NULL;
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (value)
	{
		ft_putstr("\x1b[31m");
		ft_putstr(value);
		ft_putstr("\x1b[0m");
	}
	ft_putstr("\x1b[32m");
	ft_putstr("/$>  ");
	ft_putstr("\x1b[0m");
}
