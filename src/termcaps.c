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

void			set_term_param(t_para *glob)
{
	check_terminal(glob);
	init_term(glob);
}

void					check_terminal(t_para *glob)
{
	char				*name;

	glob->fd = open("/dev/tty", O_RDWR);
	name = ttyname(glob->fd);
	//ft_putendl_fd(name, 2);
	//ft_putnbr_fd(glob->fd, glob->fd);
	if (!name)
	{
		ft_putendl_fd("fd incorrect", 2);
		exit(EXIT_FAILURE);
	}
	if (!(isatty(glob->fd)))
	{
		ft_putendl_fd("Not a tty", 1);
		exit(EXIT_FAILURE);
	}
}

void					init_term(t_para *glob)
{
	struct termios		term;
	const char			*tname;

	if ((tname = getenv("TERM")) == NULL)//verifier avec l env local
	{
//		ft_putendl_fd("Environement doesn't exist", 2);//
//		exit(EXIT_FAILURE);//
		tname = "xterm-256color";
	}
	if (tgetent(NULL, tname) == -1)
	{
		ft_putendl_fd("tgetent incorrect", 2);
		return (exit(EXIT_FAILURE));
	}
	if (tcgetattr(glob->fd, &term) == -1)
	{
		ft_putendl_fd("tcgetattr incorrect", 2);
		return (exit(EXIT_FAILURE));
	}
	glob->term = (t_term *)malloc(sizeof(t_term)); //a malloc
	glob->term->canon = term.c_lflag;
	glob->term->echo = term.c_lflag;
	glob->term->vim = term.c_cc[VMIN];
	glob->term->tim = term.c_cc[VTIME];
	term.c_cc[VMIN] = 1; //a checker pour eviter le segfault
	term.c_cc[VTIME] = 0; //a checker pour eviter le segfault
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(glob->fd, TCSADRAIN, &term) == -1)
		return ;
}

void			winsize(int fd, int i[2])
{
	struct winsize w;

	ioctl(fd, TIOCGWINSZ, &w);
	i[0] = w.ws_col;
	i[1] = w.ws_row;
}