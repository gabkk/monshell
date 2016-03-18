/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:45:06 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:45:08 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_flagsignal != 0)
		{
			kill(g_flagsignal, SIGKILL);
			write(3, "\n", 1);
			g_flagsignal = 0;
		}
		return ;
	}
}
