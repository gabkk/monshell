/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 15:14:34 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 13:34:45 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_sumword(char const *s, char c)
{
	int			i;
	int			g;

	g = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			g++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (g);
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			len;
	int			j;
	int			z;
	char		**t;

	if (!(i = 0) && !s)
		return (NULL);
	t = (char **)malloc(sizeof(char *) * (ft_sumword(s, c) + 1));
	if (!(z = 0) && !t)
		return (NULL);
	while (!(len = 0) && s[i] != '\0')
	{
		while (!(j = 0) && s[i] == c && s[i] != '\0')
			i++;
		while (s[i + len] != c && s[i + len] != '\0')
			len++;
		t[z] = (char *)malloc(sizeof(char) * len + 1);
		while (s[i] != c && s[i] != '\0')
			t[z][j++] = (char)s[i++];
		t[z++][j] = '\0';
	}
	t[ft_sumword(s, c)] = (char *)NULL;
	return (t);
}
