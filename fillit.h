/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:21:16 by abarnett          #+#    #+#             */
/*   Updated: 2018/06/22 11:56:58 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MINO_SIZE 21
# define R(i, cur) ((BITS(cur) & (0xF000 >> (i * 4))) << (i * 4))
# define BITS(cur) (((t_mino *)(cur->content))->mino)
# define CHAR(cur) (((t_mino *)(cur->content))->c)
# define X(cur) (((t_mino *)(cur->content))->x)
# define Y(cur) (((t_mino *)(cur->content))->y)
# define LAST(cur) (((t_mino *)(cur->content))->last)
# define CORD(cur, size) ((Y(cur) * size) + X(cur))
# define XOROR(a, b) ((a ^ b) == (a | b))

typedef struct		s_mino
{
	char			c;
	uint16_t		mino;
	uint8_t			x;
	uint8_t			y;
	int				last;
}					t_mino;

void				print_map(t_list *list, int size);
void				place_mino(uint16_t map[], t_list *mino);
int					find_spot(uint16_t map[], int size, t_list *mino, int row);
int					fill_map(uint16_t map[], int size, t_list *head);
void				map_main(t_list *head);

#endif
