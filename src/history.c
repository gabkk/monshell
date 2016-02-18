/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 11:10:12 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/09 11:10:14 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			add_to_history(char *cmd)
{
	int			fd;

	fd = open(".mshell_hist",  O_RDWR | O_CREAT | O_APPEND, 0777);
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
}

void			set_hist(t_hist **history, char *line)
{
	t_hist		*ptrh;
	t_hist		*newh;

	newh = inithist();
	if (!*history)
	{
		*history = newh;
		newh->cmd = ft_strdup(line);
		newh->next = NULL;
		return ;
	}
	ptrh = *history;
	while (ptrh->next)
		ptrh = ptrh->next;
	ptrh->next = newh;
	newh->cmd = ft_strdup(line);
	newh->next = NULL;
}

void			show_history(void)
{
	t_hist		*newhist;
	t_hist		*ptrh;
	char		*line;
	int			fd;

	newhist = NULL;
	line = NULL;
	if ((fd = open(".mshell_hist", O_RDWR)) == -1)
		return ;
	while (get_next_line(fd, &line) == 1)
		set_hist(&newhist, line);
	ptrh = newhist;
	ft_putstr("\t\t ...history...\n");
	while (ptrh)
	{
		ft_putendl(ptrh->cmd);
		ptrh = ptrh->next;
	}
	freehist(newhist);
	//penser a free la liste
	close(fd);
}

void			freehist(t_hist *newhist)
{
	t_hist		*tmphist;
	t_hist		*ptrhist;

	ptrhist = newhist;
	while (ptrhist)
	{
		tmphist = ptrhist->next;
		//free(tmphist->cmd);
		free(ptrhist);
		ptrhist = tmphist;
		//newhist = newhist->next;
	}
//	free(newhist);
}

t_hist			*inithist(void)
{
	t_hist		*newh;

	newh = (t_hist *)malloc(sizeof(t_hist));
	newh->cmd = NULL;
	newh->next = NULL;
	return (newh);
}
