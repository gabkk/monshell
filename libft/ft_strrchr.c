/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <gkuma@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 04:50:20 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 21:51:18 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	d;
	char	*snew;

	if (!s)
		return (NULL);
	snew = (char *)s;
	d = (char)c;
	i = ft_strlen((char *)s);
	while (snew[i] != d)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	if (snew[i] == d)
		while (i > 0)
		{
			snew++;
			i--;
		}
	return (snew);
}
