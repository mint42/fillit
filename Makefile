# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/07 12:55:52 by abarnett          #+#    #+#              #
#    Updated: 2019/06/20 17:52:25 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fillit
LIB := lib/libft.a

CC := gcc
FLT_OBJS := $(patsubst %.c,%.o,$(wildcard ./*.c))
INCLUDES := -I./ -I./lib/includes
CFLAGS += -g -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./lib -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(FLT_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(FLT_OBJS) $(LFLAGS)

$(LIB):
	@- make -C lib/ all

clean:
	@- $(RM) $(FLT_OBJS)
	@- make -C lib/ clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C lib/ fclean

fclean: clean

re: fclean all
