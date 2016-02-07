/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 15:21:11 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/28 04:07:47 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_rea(int const fd, char *buf, int *ret)
{
	char			tmpbuf[BUFF_SIZE + 1];
	char			*del;

	*ret = read(fd, tmpbuf, BUFF_SIZE);
	tmpbuf[*ret] = '\0';
	del = buf;
	buf = ft_strjoin(buf, tmpbuf);
	ft_strdel(&del);
	return (buf);
}

int		ft_ret_pos(int const fd, char ***line, char **buf, int *ret)
{
	char			*templn;
	int				test;

	test = 0;
	while (*ret > 0)
	{
		if ((templn = ft_strchr(*buf, '\n')) != NULL)
		{
			*templn = '\0';
			ft_strdel(*line);
			**line = ft_strdup(*buf);
			ft_memmove(*buf, templn + 1, ft_strlen(templn + 1) + 1);
			return (1);
		}
		*buf = ft_rea(fd, *buf, ret);
		test = *ret + test;
		if (*ret == 0 && test != 0)
		{
			**line = ft_strdup(*buf);
			return (1);
		}
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	int				ret;
	static char		*buf = "";

	ret = 1;
	if (!line)
		return (-1);
	if (buf[0] == '\0')
		buf = ft_strnew(0);
	if ((ft_ret_pos(fd, &line, &buf, &ret)) == 1)
		return (1);
	if (*buf == '\0')
	{
		ft_strdel(line);
		*line = ft_strnew(0);
		return (ret == -1 ? -1 : 0);
	}
	free(buf);
	return (ret == -1 ? -1 : 0);
}
