# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkuma <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/11 11:58:27 by gkuma             #+#    #+#              #
#    Updated: 2015/01/09 01:30:51 by gkuma            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CFLAGS = -Wall -Wextra -Werror -c

LFLAGS = -L libft -lft -lncurses

INC = -I includes/ -I libft/includes

SRCSDIR = src/

SRCS = main.c maillon_op.c read_input.c alloc_tab.c define_env.c builtins.c \
	error.c setenv.c unsetenv.c chdir.c pathexec.c dispatch_job.c tools.c \
	main_body.c display_prompt.c history.c default_env.c exit.c signal.c \
	termcaps.c lst_input_op.c backspace.c termcaps_history.c selector.c \
	cursor.c tool2.c backspace_op.c selector_paste.c selector_cut.c


OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(INC) -o  $(NAME) $(OBJ) $(LFLAGS)

$(OBJ): $(addprefix $(SRCSDIR),$(SRCS))
	make -C libft/
	gcc $(CFLAGS) $(INC) $(addprefix $(SRCSDIR),$(SRCS)) $(LFLAGGS)

norme:


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
