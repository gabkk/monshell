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
	newm->bkslash = 0;
	newm->parenthese_o = 0;
	newm->parenthese_f = 0;
	newm->crochet_o = 0;
	newm->crochet_f = 0;
	newm->accolade_o = 0;
	newm->accolade_f = 0;

	return (newm);
}

void				set_quoting(t_quoting **quoting, int buff)
{
	if (buff == 39)
		(*quoting)->quote += 1;
	else if (buff == 34)
		(*quoting)->dbquote += 1;
	else if (buff == 92)
		(*quoting)->bkslash = 1;
	else if (buff == 96)
		(*quoting)->bkquote += 1;
	else if (buff == 40)
		(*quoting)->parenthese_o += 1;
	else if (buff == 41)
		(*quoting)->parenthese_f += 1;
	else if (buff == 91)
		(*quoting)->crochet_o += 1;
	else if (buff == 93)
		(*quoting)->crochet_f += 1;
	else if (buff == 123)
		(*quoting)->accolade_o += 1;
	else if (buff == 125)
		(*quoting)->accolade_f += 1;

}

int					quoting_valid(t_quoting *quoting)
{
	if (quoting->quote % 2 != 0)
		return (0);
	else if (quoting->dbquote % 2 != 0)
		return (0);
	else if (quoting->bkquote % 2 != 0)
		return (0);
	else if (quoting->parenthese_o != quoting->parenthese_f)
		return (0);
	else if (quoting->crochet_o != quoting->crochet_f)
		return (0);
	else if (quoting->accolade_o != quoting->accolade_f)
		return (0);
	if (quoting->bkslash == 1)
		return (0);
	return (1);
}
//'39 "34 \92 (40 )41 {123 }125 `96 [91 ]93