/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:54:19 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 22:19:58 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	int j;
	int f;
	int i;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		f = -1;
		j = 0;
		if (s1[i] == s2[j])
			f = i;
		while (s1[i] == s2[j] && s2[j])
		{
			i++;
			j++;
		}
		if (s2[j] == '\0')
			return ((char *)s1 + f);
		if (f != -1)
			i = f;
		i++;
	}
	return (NULL);
}
