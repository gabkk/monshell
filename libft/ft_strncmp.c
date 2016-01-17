/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 18:18:48 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 19:25:03 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1len;
	size_t	s2len;
	int		difint;

	s1len = ft_strlen(s1) + 1;
	s2len = ft_strlen(s2) + 1;
	if (s1len > s2len)
		s1len = s2len;
	if (s1len > n)
		s1len = n;
	difint = ft_memcmp(s1, s2, s1len);
	return (difint);
}
