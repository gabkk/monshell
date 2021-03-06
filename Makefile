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

LFLAGS = -L libft -lft

INC = -I includes/ -I libft/includes

SRCSDIR = src/

SRCS = main.c alloc_tab.c read_input.c define_env.c builtins.c error.c \
	setenv.c unsetenv.c chdir.c pathexec.c dispatch_job.c tools.c \
	display_prompt.c history.c default_env.c exit.c \
	maillon_op.c signal.c


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
