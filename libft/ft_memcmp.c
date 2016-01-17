/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 22:07:23 by gkuma             #+#    #+#             */
/*   Updated: 2015/01/13 02:12:04 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (i < n)
	{
		a = *(unsigned char *)s1;
		b = *(unsigned char *)s2;
		if (a != b)
			return (a - b);
		i++;
		s1++;
		s2++;
	}
	return (0);
}
