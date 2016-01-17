/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:26:40 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 18:28:54 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	if (!s1 || !s2)
		return (s1);
	i = 0;
	str1 = s1;
	str2 = (char *)s2;
	if (n != 0)
	{
		while (*str1 != '\0')
			str1++;
		while (*str2 != '\0' && i < n)
		{
			*str1++ = *str2++;
			i++;
		}
		*str1 = '\0';
		return (s1);
	}
	else
		return (s1);
}
