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

void			print_prompt(t_para **glob)
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
	(*glob)->prompt_s = 0;
	if ((*glob)->env)
	{
		home = getlistevalue(&(*glob)->env, "HOME");
		name = getlistevalue(&(*glob)->env, "USER");
	}
	(*glob)->prompt_s = topbar_user(1, name);
	if (home && pwd)
		flag = ft_strncmp(pwd, home, ft_strlen(home));
	if (pwd)
		(*glob)->prompt_s += topbar_path(home, flag, pwd);
	topbar_icone(1);
	(*glob)->prompt_s += 3;
//	ft_putnbr_fd((*glob)->prompt_s , 1);

}

void			topbar_icone(int fd)
{
	ft_putstr_fd(ANSI_COLOR_LIGHT_BLUE, fd);
		ft_putstr_fd(" » ", fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
}

int			topbar_user(int fd, char *value)
{
//	ft_putstr("\x1b[38;5;fd37m");
//	ft_putendl("-------------");
	ft_putstr_fd("\x1b[0m", fd);
	ft_putstr_fd(ANSI_COLOR_LIGHT_BLUE, fd);
	if (value)
	{
		ft_putstr_fd(value, fd);
		ft_putstr_fd("|\x1b[0m", fd);
		return (ft_strlen(value) + 1);
	}
	ft_putstr_fd("|\x1b[0m", fd);
	return (1);
}

int			topbar_path(char *home, int flag, char *pwd)
{
	char		*tmp;
	int			size;

	size = 0;
	ft_putstr_fd(ANSI_COLOR_YELLOW, 1);
//	ft_putstr("\t\t");
	if (flag == 0 && home)
	{
		ft_putstr_fd("~", 1);
		tmp = ft_strsub(pwd, ft_strlen(home),\
			(ft_strlen(pwd) - ft_strlen(home)));
		ft_putstr_fd(tmp, 1);
		size = ft_strlen(tmp);
		free(tmp);
		ft_putstr_fd(ANSI_COLOR_RESET, 1);
		return (size + 1);
	}
	else
		ft_putstr_fd(pwd, 1);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
	return (ft_strlen(pwd));
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
