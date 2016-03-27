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
	int				tmp;

	tmp = 0;
	position = get_input_pos(glob);
	ptr = (*glob)->copy;
	if (position - 1 == (*glob)->total_c)
	{
		while (ptr)
		{
			add_back_input(input, ptr->c, (*glob)->total_c);
			ft_putchar_fd(ptr->c, (*glob)->fd);
			(*glob)->cursor->posy++;
			(*glob)->cursor->ymax++;
			((*glob)->cursor->posx == 0)?(tmp = (*glob)->prompt_s):(tmp = 0);
			if (((*glob)->cursor->posy + tmp) > (*glob)->term->size[0])
			{
				//(*glob)->cursor->posy--;
				add_cursor(&(*glob)->cursor);
				ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
			}
			ptr->selected = 0;
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

void		redraw_input(t_para **glob, t_input **input)
{
		int 			y;
		t_input			*ptr;
		int				i;

		i = 0;
		y = (*glob)->prompt_s + 1;//+1 pas sure
		ptr = *input;
		while (ptr)
		{
			ft_putchar_fd(ptr->c, (*glob)->fd);
			y++;
			ptr->selected = 0;
			ptr->pos[0] = i;
			(*glob)->cursor->posy++;
			(*glob)->cursor->ymax++;
			if (y > (*glob)->term->size[0])
			{
				ft_putchar_fd('\n', (*glob)->fd);
				add_cursor(&(*glob)->cursor);
				y = 1;
			}
			i++;
			ptr = ptr->next;
		}
		ft_putendl_fd("\n", 2);//debug
		ft_putstr_fd("avant reposision =|posy: ", 2);//debug
		ft_putnbr_fd((*glob)->cursor->posy, 2);//debug
		ft_putstr_fd("|posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);
}

void		position_cursor(t_para **glob, int final)
{
		int xfinal;
		int yfinal;

		xfinal = 0;
		yfinal = (*glob)->prompt_s;
		while (final > 0)
		{
			yfinal++;
			if (yfinal > (*glob)->term->size[0])
			{
				xfinal++;
				yfinal = 1;
			}
			final--;
		}



	if ((*glob)->cursor->posx > xfinal)// dans le cas sup a zero
	{
		// if (xfinal == 0)
		// 	yfinal -=(*glob)->prompt_s;
		
		ft_putendl_fd("up", 2);//debug
		ft_putchar_fd('\n', 2);//debug
		ft_putstr_fd("|xfinal:", 2);
		ft_putnbr_fd(xfinal, 2);
		ft_putstr_fd("|yfinal:", 2);
		ft_putnbr_fd(yfinal, 2);//debug
		ft_putstr_fd("|(*glob)->cursor->posy:", 2);
		ft_putnbr_fd((*glob)->cursor->posy, 2);//debug
		ft_putstr_fd("|(*glob)->cursor->posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);//debug


		if ((*glob)->cursor->posy < yfinal)
		{
			ft_putstr_fd("|1", 2);
			while ((*glob)->cursor->posy < yfinal)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
			}
		}
		else if ((*glob)->cursor->posy > yfinal)
		{
			ft_putstr_fd("|2", 2);
			while ((*glob)->cursor->posy > yfinal)
			{
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				(*glob)->cursor->posy--;
			}
		}
		// else if ((*glob)->cursor->posy == yfinal && (*glob)->cursor->ymax == 0)
		// {
		// 	ft_putstr_fd("|3", 2);
		//  	ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);	
		// }
		// else if (yfinal == (*glob)->term->size[0])
		// 	ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);
		while ((*glob)->cursor->posx > xfinal)// dans le cas sup a zero
		{
			ft_putstr_fd(tgetstr("up", NULL), (*glob)->fd);
			if ((*glob)->cursor->prev)
			{
				(*glob)->cursor->posy = 1;
				(*glob)->cursor = (*glob)->cursor->prev;
			}
		}
		if ((*glob)->cursor->posx == 0)
			yfinal -= (*glob)->prompt_s;
		(*glob)->cursor->posy = yfinal;
	}
	else
	{
		if ((*glob)->cursor->posx == 0)
			yfinal -= (*glob)->prompt_s;

		ft_putendl_fd("down", 2);//debug
		ft_putchar_fd('\n', 2);//debug
		ft_putstr_fd("|xfinal:", 2);
		ft_putnbr_fd(xfinal, 2);
		ft_putstr_fd("|yfinal:", 2);
		ft_putnbr_fd(yfinal, 2);//debug
		ft_putstr_fd("|(*glob)->cursor->posy:", 2);
		ft_putnbr_fd((*glob)->cursor->posy, 2);//debug
		ft_putstr_fd("|(*glob)->cursor->posx:", 2);
		ft_putnbr_fd((*glob)->cursor->posx, 2);//debug
		ft_putstr_fd("|(*glob)->cursor->ymax:", 2);
		ft_putnbr_fd((*glob)->cursor->ymax, 2);//debug

		if ((*glob)->cursor->posy < yfinal)
		{
		ft_putstr_fd("|1", 2);
			while ((*glob)->cursor->posy < yfinal)
			{
				ft_putstr_fd(tgetstr("nd", NULL), (*glob)->fd);
				(*glob)->cursor->posy++;
			}
		}
		else if ((*glob)->cursor->posy > yfinal)
		{
		ft_putstr_fd("|2", 2);
			while ((*glob)->cursor->posy > yfinal)
			{
				ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
				(*glob)->cursor->posy--;
			}
		}
		// else if ((*glob)->cursor->posy == yfinal && (*glob)->cursor->ymax == 0)
		// {
		// 	ft_putstr_fd("|3", 2);
		//  	ft_putstr_fd(tgetstr("do", NULL), (*glob)->fd);	
		// }
		// {
		// 	ft_putstr_fd("oue", 2);//debug
		// 	ft_putstr_fd(tgetstr("le", NULL), (*glob)->fd);
		// }
	}
}