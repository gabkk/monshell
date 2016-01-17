/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:41:04 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 19:06:48 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	int				f;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		f = -1;
		j = 0;
		if (s1[i] == s2[j])
			f = i;
		while (s1[i] == s2[j] && s2[j] && i < n)
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
