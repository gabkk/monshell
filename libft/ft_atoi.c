/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <gkuma@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/03 04:50:20 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 19:27:06 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_whitesp(const char *str, int i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\v'\
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n'))
	{
		i++;
	}
	return (i);
}

static int		ft_minus(const char *str, int i, int neg)
{
	if (str[i] == 45)
	{
		neg = 1;
	}
	return (neg);
}

static int		ft_isneg(int neg, int rst)
{
	if (neg == 1)
	{
		rst = -rst;
	}
	return (rst);
}

int				ft_atoi(const char *str)
{
	int i;
	int rst;
	int neg;

	i = 0;
	rst = 0;
	neg = 0;
	i = (ft_whitesp(str, i));
	if (str[i] == 43 || str[i] == 45)
	{
		neg = ft_minus(str, i, neg);
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			rst = rst * 10 + ((char)str[i] - 48);
		else
		{
			return (rst = ft_isneg(neg, rst));
		}
		i++;
	}
	return (rst = ft_isneg(neg, rst));
}
