/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:41:31 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:41:33 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quoting			*init_quoting()
{
	t_quoting		*newm;

	newm = (t_quoting *)malloc(sizeof(t_quoting));
	newm->quote = 0;
	newm->dbquote = 0;
	newm->bkquote = 0;
	newm->parenthese = 0;
	newm->crochet = 0;
	newm->accolade = 0;

	return (newm);
}

//	check_quoting();
