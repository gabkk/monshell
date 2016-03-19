/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:48:46 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/13 12:45:48 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == ' ')
	{
		return (1);
	}
	return (0);
}
