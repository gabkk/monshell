/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 06:37:41 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 13:05:24 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*t;
	unsigned int	i;
	unsigned int	size;

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
		t[i] = (*f)(i, s[i]);
		i++;
	}
	t[i] = '\0';
	return (t);
}
