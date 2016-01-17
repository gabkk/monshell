/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 05:50:17 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 13:05:06 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*t;
	int		i;
	int		size;

	size = 0;
	i = 0;
	if (!s || !f)
		return (NULL);
	while (s[size] != '\0')
	{
		size++;
	}
	t = (char *)malloc(sizeof(char) * size + 1);
	while (i < size)
	{
		t[i] = (*f)(s[i]);
		i++;
	}
	t[i] = '\0';
	return (t);
}
