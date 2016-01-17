/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 02:54:28 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 12:49:41 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void		*ptr;
	size_t		i;

	i = 0;
	ptr = malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	while (i < size)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
