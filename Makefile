# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/07 12:55:52 by abarnett          #+#    #+#              #
#    Updated: 2018/06/22 11:24:11 by abarnett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fillit
LIB := libft.a
C_OBJS := $(patsubst %.c,%.o,$(wildcard ./*.c))
L_OBJS := $(patsubst %.c,%.o,$(wildcard ./libft/*.c))
INCLUDE_DIRS := ./libft
CFLAGS += -Wall -Wextra -Werror -I$(INCLUDE_DIRS)
LDFLAGS += -L./ -lft

.PHONY: all clean fclean re

all: $(NAME)

$(LIB): $(L_OBJS)
	ar rc $(LIB) $(L_OBJS)
	ranlib $(LIB)

$(NAME): $(LIB) $(C_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(C_OBJS) $(LDFLAGS)

clean:
	@- $(RM) $(C_OBJS) $(L_OBJS)

fclean: clean
	@- $(RM) $(NAME) $(LIB)

re: fclean all
