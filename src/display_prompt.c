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
	char		*name;
	char		*home;
	int			flag;
	char		buff[PATH_MAX];
	char		*pwd;

	pwd = getcwd(buff, PATH_MAX);
	flag = 1;
	home = NULL;
	name = NULL;
	if (env)
	{
		home = getlistevalue(&env, "HOME");
		name = getlistevalue(&env, "USER");
	}
	topbar_user(name);
	if (home && pwd)
		flag = ft_strncmp(pwd, home, ft_strlen(home));
	if (pwd)
		topbar_path(home, flag, pwd);
	topbar_icone();
}

void			topbar_icone()
{
	ft_putstr(ANSI_COLOR_LIGHT_BLUE);
		ft_putstr(" » ");
	ft_putstr(ANSI_COLOR_RESET);
}

void			topbar_user(char *value)
{
//	ft_putstr("\x1b[38;5;237m");
//	ft_putendl("-------------");
	ft_putstr("\x1b[0m");
	ft_putstr(ANSI_COLOR_LIGHT_BLUE);
	if (value)
		ft_putstr(value);
	ft_putstr("|\x1b[0m");
}

void			topbar_path(char *home, int flag, char *pwd)
{
	char		*tmp;

	ft_putstr(ANSI_COLOR_YELLOW);
//	ft_putstr("\t\t");
	if (flag == 0 && home)
	{
		ft_putstr("~");
		tmp = ft_strsub(pwd, ft_strlen(home),\
			(ft_strlen(pwd) - ft_strlen(home)));
		ft_putstr(tmp);
		free(tmp);
	}
	else
		ft_putstr(pwd);
	ft_putstr(ANSI_COLOR_RESET);
}

void			print_intro(void)
{
	ft_putendl("___  ____       _     _          _ _ ");
	ft_putendl("|  \\/  (_)     (_)   | |        | | |");
	ft_putendl("| .  . |_ _ __  _ ___| |__   ___| | |");
	ft_putendl("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |");
	ft_putendl("| |  | | | | | | \\__ \\ | | |  __/ | |");
	ft_putendl("\\_|  |_/_|_| |_|_|___/_| |_|\\___|_|_|");
	ft_putendl("");
	ft_putendl("");
}
