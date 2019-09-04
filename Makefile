# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/07 12:55:52 by abarnett          #+#    #+#              #
#    Updated: 2019/09/04 15:09:20 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fillit
LIB := libft/libft.a

CC := gcc
FLT_OBJS := $(patsubst %.c,%.o,$(wildcard ./*.c))
INCLUDES := -I./ -I./libft/includes
CFLAGS += -g -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./libft -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(FLT_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(FLT_OBJS) $(LFLAGS)

$(LIB):
	@- make -C libft/ all

clean:
	@- $(RM) $(FLT_OBJS)
	@- make -C libft/ clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft/ fclean

fclean: clean

re: fclean all
