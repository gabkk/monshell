/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:48:46 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 14:53:11 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strtrim(char const *s)
{
	int		start;
	char	*t;
	int		end;
	int		i;

	if (!(i = 0) && !s)
		return (NULL);
	while (s[i] == 32 || s[i] == 10 || s[i] == 9)
		i++;
	start = i;
	i = ft_strlen(s) - (ft_strlen(s) == 0 ? 0 : 1);
	while (s[i] == 32 || s[i] == 10 || s[i] == 9)
		i--;
	end = i + 1;
	t = (char *)malloc(sizeof(char) * \
			((end - start) > 0 ? (end - start) : 1));
	if (!(i = 0) && !t)
		return (NULL);
	while (i < (end - start))
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
