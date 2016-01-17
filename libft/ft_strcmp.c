/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:48:52 by gkuma             #+#    #+#             */
/*   Updated: 2015/03/22 20:09:09 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	int		difint;

	s1len = ft_strlen(s1) + 1;
	s2len = ft_strlen(s2) + 1;
	if (s1len > s2len)
		s1len = s2len;
	difint = ft_memcmp(s1, s2, s1len);
	return (difint);
}
