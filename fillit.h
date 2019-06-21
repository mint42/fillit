/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:21:16 by abarnett          #+#    #+#             */
/*   Updated: 2019/06/20 20:13:10 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdint.h>

# define MINO_SIZE 16
# define BUFF_SIZE 21
# define MAX_TETROMINOS 26
# define MAX_BOARD_SIZE 16

# define C(cur) (((t_mino *)((cur)->content))->c)
# define MINO(cur) (((t_mino *)((cur)->content))->mino)
# define X(cur) (((t_mino *)((cur)->content))->x)
# define Y(cur) (((t_mino *)((cur)->content))->y)
# define LAST(cur) (((t_mino *)((cur)->content))->last)

# define ROW(row, cur) ((MINO(cur) & (0xF000 >> ((row) * 4))) << ((row) * 4))
# define CORD(cur, map_size) ((Y(cur) * (map_size)) + X(cur))

# define XOROR(a, b) ((a ^ b) == (a | b))

typedef struct		s_mino
{
	char			c;
	uint16_t		mino;
	uint8_t			x;
	uint8_t			y;
	int				last;
}					t_mino;

typedef struct s_list	t_list;

void				map_main(t_list *head);

#endif
