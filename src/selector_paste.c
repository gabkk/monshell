/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 13:28:44 by gkuma             #+#    #+#             */
/*   Updated: 2016/02/07 13:28:46 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			save_copy(t_para **glob, t_input **input)
{
	t_input			*ptr;
	int				position;

	position = get_input_pos(glob);
	ptr = (*glob)->copy;
	if (position - 1 == (*glob)->total_c)
	{
		while (ptr)
		{
			add_back_input(input, ptr->c, (*glob)->total_c);
			ft_putchar_fd(ptr->c, (*glob)->fd);
			ptr->selected = 0;
			(*glob)->cursor->posy++;
			(*glob)->cursor->ymax++;
			if ((*glob)->cursor->posy > (*glob)->term->size[0])
			{
				(*glob)->cursor->posy--;
				add_cursor(&(*glob)->cursor);
			}
			(*glob)->total_c += 1;
			ptr = ptr->next;
		}
		return (-1);
	}
	else
	{
		while (ptr)
		{
			add_inside_input(input, ptr->c, position);
			position++;
			(*glob)->total_c += 1;
			ptr = ptr->next;
		}
		return (position);
	}
}

void		redraw_with_copy(t_para **glob, t_input **input)
{
		int 			y;
		t_input			*ptr;

		y = (*glob)->prompt_s + 1;//+1 pas sure
		ptr = *input;
		while (ptr)
		{
			ft_putchar_fd(ptr->c, (*glob)->fd);
			y++;
			ptr->selected = 0;
			(*glob)->cursor->posy++;
			(*glob)->cursor->ymax++;
			if (y > (*glob)->term->size[0])
			{
				add_cursor(&(*glob)->cursor);
				y = 1;
			}
			ptr = ptr->next;
		}
		ft_putendl_fd("\n", 2);//debug
		ft_putstr_fd("avant reposision =|posy: ", 2);//debug
		ft_putnbr_fd((*glob)->cursor->posy, 2);//debug
		ft_putstr_fd("|posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);
}