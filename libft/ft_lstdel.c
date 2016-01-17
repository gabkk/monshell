/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 18:06:52 by gkuma             #+#    #+#             */
/*   Updated: 2014/11/14 18:39:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *glasses;

	if (!alst || !*alst || !(*del))
		return ;
	while (*alst)
	{
		(*del)((*alst)->content, (*alst)->content_size);
		glasses = *alst;
		free(*alst);
		*alst = glasses->next;
	}
	*alst = NULL;
}
