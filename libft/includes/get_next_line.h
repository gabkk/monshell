/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <gkuma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 22:57:37 by gkuma             #+#    #+#             */
/*   Updated: 2015/05/15 18:23:06 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 445

typedef struct		s_content
{
	char *offset[2];
	char buf[BUFF_SIZE + 1];
}					t_content;

int					get_next_line(int const fd, char **line);
char				*concat_list(t_list **elem_a, size_t size);
int					build_str(int fd, t_list **elem_a, size_t *size);
int					search_for_end(t_content *content, int max_size);
int					pull_list(t_list **elem_a, t_content *content);

#endif

