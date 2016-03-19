/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:44:48 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:44:52 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			show_last_hist(t_para **glob, t_input **input)
{
	char		*line;
	int			fd;
	int			i;
	int			j;

	j = 0;
	i = 0;
	line = NULL;
	(*glob)->cursor[0] = 0;
	(*glob)->total_c = 0;
	if ((fd = open(PATH_HIST, O_RDWR | O_CREAT, 0777)) == -1)
		return (ft_putstr_fd("open error : hist", 2));
	while (get_next_line(fd, &line) == 1)
	{
		if (i == (*glob)->current_h - 1)
		{
			while (line[j] != '\0')
			{
				ft_putchar_fd(line[j], (*glob)->fd);
				add_back_input(input, line[j], j);
				(*glob)->cursor[0]++;
				(*glob)->total_c +=1 ;
				j++;
			}
			break;
		}
		i++;
	}
	free(line);
	close(fd);
}

void			tot_hist(t_para **glob)
{
	char		*line;
	int			fd;
	int			i;

	i = 0;
	line = NULL;
	if ((fd = open(PATH_HIST, O_RDWR | O_CREAT, 0777)) == -1)
		return ;
	while (get_next_line(fd, &line) == 1)
		i++;
	(*glob)->total_h = i + 1;
	(*glob)->current_h = i + 1;
	free(line);
	close(fd);
}