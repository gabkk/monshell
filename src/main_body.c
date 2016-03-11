/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:52:38 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:52:41 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			mainbody(t_para *glob)
{
	g_flagsignal = 0;
	if (!glob->env)
		glob->env = setdefaultenv();
	glob->term->action = 0;
	print_prompt(glob);
	//ft_putstr_fd("yo 1", glob->fd);
	main_loop(glob);
}

void					main_loop(t_para *glob)
{
	t_input		*input;
	int			index;

	input = NULL;
	index = 0;
	while (42)
	{
		read_input(glob, &input, &index);
		if (glob->cmd && glob->term->action == 1)
		{
			main_action(glob);
			index = 0;	
		}
	}
}

void			main_action(t_para *glob)
{
	t_cmd		*ptrmaillon;
	t_cmd		*base;

	ptrmaillon = NULL;
	base = read_cmd(glob);
	if (glob->term->action == 1)
	{
		ptrmaillon = base;
		while (ptrmaillon)
		{
			if (ptrmaillon->listcmd)
				dispatch(&glob->env, ptrmaillon->listcmd);
			ptrmaillon = ptrmaillon->next;
		}
		freebase(&base);
		glob->term->action = 0;
		print_prompt(glob);
	}
}