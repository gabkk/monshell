/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int ac, char *const av[], char *const envp[])
{
	t_env		*env;
	t_para		*glob;

	env = NULL;
	(void)ac;
	(void)av;
	glob = (t_para *)malloc(sizeof(t_para));
	env = getlocalenv(envp);
	//print_intro(); // For tests
	set_term_param(glob);
	tot_hist(&glob);
	if (env)
		setlistlvl(&env);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putendl("sig error");
	glob->env = env;
	glob->cursor[0] = 0;
	glob->cursor[1] = 0;
	mainbody(glob);
	freenv(glob->env);
	close(glob->fd);
	//free all glob
	return (0);
}
