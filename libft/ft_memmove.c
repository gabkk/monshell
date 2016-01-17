/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 18:52:05 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 18:05:24 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	tab[len];
	size_t			i;

	i = 0;
	while (i < len && src)
	{
		tab[i] = *(unsigned char *)(src + i);
		i++;
	}
	i = 0;
	while (i < len && dst)
	{
		*(unsigned char *)(dst + i) = tab[i];
		i++;
	}
	return (dst);
}
