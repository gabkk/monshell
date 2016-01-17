/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 14:16:54 by gkuma             #+#    #+#             */
/*   Updated: 2015/01/16 05:11:02 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_lstpushb(void *content, t_liste **liste, size_t content_size)
{
	t_liste		*newmaillon;
	t_liste		*ptrmaillon;

	newmaillon = ft_lstnew(content, content_size);
	if (!newmaillon)
		return ;
	if (*liste == NULL)
	{
		*liste = newmaillon;
		return ;
	}
	ptrmaillon = *liste;
	while (ptrmaillon->next)
		ptrmaillon = ptrmaillon->next;
	ptrmaillon->next = newmaillon;
}
