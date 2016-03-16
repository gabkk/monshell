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

void			tot_hist(t_para **glob)
{
	char		*line;
	int			fd;
	int			i;

	i = 0;
	line = NULL;
	if ((fd = open(".mshell_hist", O_RDWR)) == -1)
		return ;
	while (get_next_line(fd, &line) == 1)
		i++;
	(*glob)->total_h = i;
	(*glob)->current_h = i - 1;
	free(line);
	close(fd);
}

void			show_last_hist(t_para **glob)
{
	char		*line;
	int			fd;
	int			i;
	int			j;

	j = 0;
	i = 0;
	line = NULL;
	(*glob)->cursor[0] = 0;
	if ((fd = open(".mshell_hist", O_RDWR)) == -1)
		return ;
	while (get_next_line(fd, &line) == 1)
	{
		if (i == (*glob)->current_h)
		{
			while (line[j] != '\0')
			{
				ft_putchar_fd(line[j], (*glob)->fd);
				(*glob)->cursor[0]++;
				j++;
			}
		}
		i++;
	}
	free(line);
	close(fd);
}

void			clear_screen(t_para *glob)
{
	int 		i;

	i = glob->cursor[0];
	while (i > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), glob->fd);
		i--;	
	}
	while (i < glob->cursor[0])
	{
		ft_putchar_fd(' ', glob->fd);
		i++;
	}
	i = glob->cursor[0];
	while (i > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), glob->fd);
		i--;
	}
}