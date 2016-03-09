/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_term_param(t_env *env)
{
	check_terminal(env);
	init_term(env);
}

void					check_terminal(t_env *env)
{
	char				*name;

	name = ttyname(0);
	if (!name)
	{
		ft_putendl_fd("fd incorrect", 2);
		exit(EXIT_FAILURE);
	}
	env->fd = open(name, O_RDWR | O_NONBLOCK);
	if (!(isatty(env->fd)))
	{
		ft_putendl_fd("Not a tty", 1);
		exit(EXIT_FAILURE);
	}
}

void					init_term(t_env *env)
{
	struct termios		term;
	const char			*tname;

	if ((tname = getenv("TERM")) == NULL)//verifier avec l env local
	{
		ft_putendl_fd("Environement doesn't exist", 2);
		exit(EXIT_FAILURE);
	}
	if (tgetent(NULL, tname) == -1){
		ft_putendl_fd("tgetent incorrect", 2);

		return (exit(EXIT_FAILURE));
	}
	if (tcgetattr(0, &term) == -1){
		ft_putendl_fd("tcgetattr incorrect", 2);
		
		return (exit(EXIT_FAILURE));
	}
	env->term = (t_term *)malloc(sizeof(t_term)); //a malloc
	env->term->canon = term.c_lflag;
	env->term->echo = term.c_lflag;
	env->term->vim = term.c_cc[VMIN];
	env->term->tim = term.c_cc[VTIME];
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return ;
}
