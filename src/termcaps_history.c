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
	int			y;

	y = (*glob)->prompt_s;
	j = 0;
	i = 0;
	line = NULL;
	(*glob)->cursor->posy = 1;
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
				
				if (y == (*glob)->term->size[0])
				{

					add_cursor(&(*glob)->cursor);
					y = 0;


				ft_putendl_fd("!1", 2);//debug
				ft_putstr_fd("(*glob)->cursor->posx", 2);//debug
				ft_putnbr_fd((*glob)->cursor->posx, 2);//debug

				}
				y++;
				(*glob)->cursor->ymax++;
				(*glob)->cursor->posy++;
				(*glob)->total_c +=1 ;
				j++;

			}
			if (y == (*glob)->term->size[0])
			{
			//	(*glob)->cursor->posy--;
				ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
				add_cursor(&(*glob)->cursor);
			//	(*glob)->cursor->ymax++;
				(*glob)->cursor->posy = 1;
				ft_putendl_fd("!2", 2);//debug
				ft_putstr_fd("(*glob)->cursor->posx", 2);//debug
				ft_putnbr_fd((*glob)->cursor->posx, 2);//debug
			}
				ft_putendl_fd("", 2);//debug
				ft_putstr_fd("(*glob)->cursor->posy", 2);//debug
				ft_putnbr_fd((*glob)->cursor->posy, 2);//debug
				// ft_putstr_fd("y", 2);//debug
				// ft_putnbr_fd(y, 2);//debug

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