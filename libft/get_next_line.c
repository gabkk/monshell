/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <gkuma>@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 15:21:11 by gkuma             #+#    #+#             */
/*   Updated: 2015/05/15 18:22:38 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		get_next_line(int const fd, char **line)
{
	t_list				*elem_a[2];
	int					trigger;
	size_t				size;

	if ((fd == 1 || fd == 2 || fd < 0) || line == NULL)
		return (-1);
	trigger = 0;
	size = 0;
	ft_bzero(elem_a, 2 * sizeof(t_list *));
	while (trigger == 0)
	{
		trigger = build_str(fd, elem_a, &size);
		if (trigger == -1)
			return (-1);
	}
	if (elem_a[0] == NULL)
	{
		*line = NULL;
		return (0);
	}
	if ((*line = concat_list(elem_a, size)) == NULL)
		return (-1);
	return (1);
}

int		build_str(int fd, t_list **elem_a, size_t *size)
{
	int					cnt_read;
	static t_content	content;
	int					trigger;

	trigger = 0;
	if (content.offset[0] != NULL && *(content.offset[0]) != 0)
	{
		trigger = search_for_end(&content, ft_strlen(content.offset[0]));
		*size += content.offset[1] - content.offset[0];
		if (pull_list(elem_a, &content) == 1)
			return (-1);
	}
	else
	{
		ft_bzero(content.buf, BUFF_SIZE + 1);
		cnt_read = read(fd, content.buf, BUFF_SIZE);
		if (cnt_read == -1)
			return (-1);
		if (cnt_read == 0)
			return (1);
		content.offset[0] = content.buf;
	}
	return (trigger);
}

char	*concat_list(t_list **elem_a, size_t size)
{
	char *line;
	char *str_p;

	line = ft_memalloc(size + 1);
	if (line == NULL)
		return (NULL);
	str_p = line;
	elem_a[1] = elem_a[0];
	while (elem_a[1] != NULL)
	{
		str_p = ft_strncat(str_p, elem_a[1]->content, elem_a[1]->content_size);
		str_p = str_p + elem_a[1]->content_size;
		elem_a[1] = elem_a[1]->next;
	}
	while (elem_a[0] != NULL)
	{
		elem_a[1] = elem_a[0]->next;
		free(elem_a[0]->content);
		free(elem_a[0]);
		elem_a[0] = elem_a[1];
	}
	return (line);
}

int		search_for_end(t_content *content, int max_size)
{
	char	*character_p;

	character_p = ft_memchr(content->offset[0], '\n', max_size);
	if (character_p != NULL)
	{
		content->offset[1] = character_p;
		return (1);
	}
	else
	{
		content->offset[1] = content->offset[0] + max_size;
		return (0);
	}
}

int		pull_list(t_list **elem_a, t_content *content)
{
	size_t	size;

	size = content->offset[1] - content->offset[0];
	if (elem_a[0] != NULL)
	{
		elem_a[1]->next = ft_lstnew(content->offset[0], size);
		if (elem_a[1]->next == NULL)
			return (1);
		elem_a[1] = elem_a[1]->next;
	}
	else
	{
		elem_a[0] = ft_lstnew(content->offset[0], size);
		if (elem_a[0] == NULL)
			return (1);
		elem_a[1] = elem_a[0];
	}
	content->offset[0] = content->offset[1] + 1;
	return (0);
}

// char	*ft_rea(int const fd, char *buf, int *ret)
// {
// 	char			tmpbuf[BUFF_SIZE + 1];
// 	char			*del;

// 	*ret = read(fd, tmpbuf, BUFF_SIZE);
// 	tmpbuf[*ret] = '\0';
// 	del = buf;
// 	buf = ft_strjoin(buf, tmpbuf);
// 	ft_strdel(&del);
// 	return (buf);
// }

// int		ft_ret_pos(int const fd, char ***line, char **buf, int *ret)
// {
// 	char			*templn;
// 	int				test;

// 	test = 0;
// 	while (*ret > 0)
// 	{
// 		if (*buf && (templn = ft_strchr(*buf, '\n')) != NULL)
// 		{
// 			*templn = '\0';
// 			ft_strdel(*line);
// 			**line = ft_strdup(*buf);
// 			ft_memmove(*buf, templn + 1, ft_strlen(templn + 1) + 1);
// 			return (1);
// 		}
// 		*buf = ft_rea(fd, *buf, ret);
// 		test = *ret + test;
// 		if (*ret == 0 && test != 0)
// 		{
// 			**line = ft_strdup(*buf);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int		get_next_line(int const fd, char **line)
// {
// 	int				ret;
// 	static char		*buf;

// 	ret = 1;
// 	if (!line)
// 		return (-1);
// 	buf = NULL;
// 	if ((ft_ret_pos(fd, &line, &buf, &ret)) == 1)
// 		return (1);
// 	if (*buf == '\0')
// 	{
// 		ft_strdel(line);
// 		*line = ft_strnew(0);
// 		return (ret == -1 ? -1 : 0);
// 	}
// 	free(buf);
// 	return (ret == -1 ? -1 : 0);
// }
