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

void			print_prompt(t_para *glob)
{
	char		*name;
	char		*home;
	int			flag;
	char		buff[PATH_MAX];
	char		*pwd;

	pwd = getcwd(buff, PATH_MAX);
	flag = 1;
	home = NULL;
	name = NULL;
	if (glob->env)
	{
		home = getlistevalue(&glob->env, "HOME");
		name = getlistevalue(&glob->env, "USER");
	}
	topbar_user(glob->fd, name);
	if (home && pwd)
		flag = ft_strncmp(pwd, home, ft_strlen(home));
	if (pwd)
		topbar_path(glob->fd, home, flag, pwd);
	topbar_icone(glob->fd);
}

void			topbar_icone(int fd)
{
	ft_putstr_fd(ANSI_COLOR_LIGHT_BLUE, fd);
		ft_putstr_fd(" » ", fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
}

void			topbar_user(int fd, char *value)
{
//	ft_putstr("\x1b[38;5;fd37m");
//	ft_putendl("-------------");
	ft_putstr_fd("\x1b[0m", fd);
	ft_putstr_fd(ANSI_COLOR_LIGHT_BLUE, fd);
	if (value)
		ft_putstr_fd(value, fd);
	ft_putstr_fd("|\x1b[0m", fd);
}

void			topbar_path(int fd, char *home, int flag, char *pwd)
{
	char		*tmp;

	ft_putstr_fd(ANSI_COLOR_YELLOW, fd);
//	ft_putstr("\t\t");
	if (flag == 0 && home)
	{
		ft_putstr_fd("~", fd);
		tmp = ft_strsub(pwd, ft_strlen(home),\
			(ft_strlen(pwd) - ft_strlen(home)));
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	else
		ft_putstr_fd(pwd, fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
}

void			print_intro(int fd)
{
	ft_putendl_fd("___  ____       _     _          _ _ ", fd);
	ft_putendl_fd("|  \\/  (_)     (_)   | |        | | |", fd);
	ft_putendl_fd("| .  . |_ _ __  _ ___| |__   ___| | |", fd);
	ft_putendl_fd("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |", fd);
	ft_putendl_fd("| |  | | | | | | \\__ \\ | | |  __/ | |", fd);
	ft_putendl_fd("\\_|  |_/_|_| |_|_|___/_| |_|\\___|_|_|", fd);
	ft_putendl_fd("", fd);
	ft_putendl_fd("", fd);
}
