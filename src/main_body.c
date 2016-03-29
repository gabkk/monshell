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

	print_prompt(&glob);
	//ft_putstr_fd("yo 1", glob->fd);
	main_loop(glob);
}

void					main_loop(t_para *glob)
{
	t_input		*input;

	input = NULL;
	glob->total_c = 0;
	glob->cursor->ymax = 0;
	while (42)
	{
		read_input(glob, &input);
		if (glob->cmd && glob->term->action == 1)
		{
			main_action(&glob);
			glob->total_c = 0;
			freecursor(&glob->cursor);
			free(glob->quoting);
			glob->cursor = init_cursor();
			glob->quoting = init_quoting();
			glob->selector = 0;
			glob->term->action = 0;
			//free glob->quoting
			print_prompt(&glob);
		}
	}
}

void			main_action(t_para **glob)
{
	t_cmd		*ptrmaillon;
	t_cmd		*base;

	ptrmaillon = NULL;
	base = NULL;
	parse_value(glob, &base);
	if ((*glob)->term->action == 1)
	{
		add_to_history((*glob)->cmd);
		free((*glob)->cmd);
		(*glob)->total_h += 1;
		(*glob)->current_h = (*glob)->total_h;
		ptrmaillon = base;
		while (ptrmaillon)
		{
			if (ptrmaillon->listcmd)
				dispatch(&(*glob)->env, ptrmaillon->listcmd);
			ptrmaillon = ptrmaillon->next;
		}
		freebase(&base);
	}
}

void			parse_value(t_para **glob, t_cmd **base)
{
	int			i;
	char		**cmd;
	char		**tmp;

	i = 0;
	tmp = NULL;
	if ((checkifonlyspace((*glob)->cmd) == 1))
	{
		(*glob)->term->action = 0;
		free((*glob)->cmd);
	}
	else
	{
		cmd = ft_strsplit((*glob)->cmd, ';');
		if (!*cmd)
			return ;
		while (cmd[i])
		{
			tmp = parse_cmd(cmd[i]);
			if (tmp)
				add_maillon_cmd(tmp, base);
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}
