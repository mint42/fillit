# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 00:16:25 by rreedy            #+#    #+#              #
#    Updated: 2019/06/20 20:05:16 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
INCLUDES := -I./includes -I./includes/ft_printf
CFLAGS += -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./ -lft
MODS := ft_list\
		ft_mem\
		ft_put\
		ft_str\
		ft_utils\
#		ft_conv\
#		ft_double_array\
#		ft_binarytree\
#		ft_math\
#		ft_printf\
#		ft_queue\
#		ft_stack\
#		get_next_line

NAME_COLOR := \e[1;33m
COMPILE_COLOR := \e[1;32m
DOTS_COLOR := \e[0;36m
FINISH_COLOR := \e[0;32m
CLEAR_COLOR := \e[m
DELETE_COLOR := \e[0;31m
