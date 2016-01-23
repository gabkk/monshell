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

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -c

LFLAGS = -L libft -lft

INC = -I includes/ -I libft/includes

SRCSDIR = src/

SRCS = main.c commandLineAction.c defineEnv.c builtins.c error.c setenv.c \
		unsetenv.c

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
