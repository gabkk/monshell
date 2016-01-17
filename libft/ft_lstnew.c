/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:48:46 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 17:51:06 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;
	void	*c;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (content == NULL)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		c = malloc(content_size);
		if (c == NULL)
			return (NULL);
		node->content = ft_memcpy(c, content, content_size);
		node->content_size = content_size;
	}
	node->next = NULL;
	return (node);
}
