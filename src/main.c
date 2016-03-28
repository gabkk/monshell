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
	winsize(glob->fd, glob->term->size);
	tot_hist(&glob);
	if (env)
		setlistlvl(&env);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putendl("sig error");
	//ft_putnbr_fd(glob->term->size[0] , glob->fd);
	// ft_putnbr_fd(glob->term->size[1] , glob->fd);
	glob->env = env;
	glob->current_l = 0;	
	glob->cursor = init_cursor();//a free
	glob->copy = NULL;
	glob->selector = 0;
	glob->quoting = init_quoting();//a free
	mainbody(glob);
	freenv(glob->env);
	close(glob->fd);
	//free all glob
	//free quoting
	return (0);
}
