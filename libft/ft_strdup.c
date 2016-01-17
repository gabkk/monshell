/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:27:53 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/15 18:10:30 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	int				j;
	char			*s2;

	j = 0;
	i = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * i + 1);
	if (!s2)
		return (NULL);
	while (s1[j] != '\0')
	{
		s2[j] = *(char *)(s1 + j);
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
