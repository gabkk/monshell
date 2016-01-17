/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 00:17:30 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 14:39:00 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_getlen(int nb, int neg)
{
	int		i;

	i = 0;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	i++;
	if (neg == 1)
		i++;
	return (i);
}

static char		*ft_isintmax(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	str = ft_strcpy(str, "-2147483648");
	return (str);
}

char			*ft_itoa(int c)
{
	int		neg;
	int		len;
	char	*str;

	if (c == -2147483648)
		return (ft_isintmax());
	neg = 0;
	if (c < 0)
	{
		c = -c;
		neg = 1;
	}
	len = ft_getlen(c, neg);
	str = (char *)malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = (c % 10) + 48;
		c = c / 10;
		len--;
	}
	if (neg == 1)
		str[len] = '-';
	return (str);
}
