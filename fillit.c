/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:48:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/06/20 20:22:18 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_put.h"
#include "ft_list.h"

/*
**	The print_map() function allocates a char pointer called s, which is used
**	hold the map with the letters of the tetromino pieces, and then will be
**	printed by ft_putendl(). This function first has a while loop to place the
**	newlines into the string, and then the main while loop, which loops through
**	the linked list	and places characters on the board using bit
**	shifting on the tetromino piece starting at its x and y coordinates.
*/

static void		print_map(t_list *tetrominos, int map_size)
{
	char	*s;
	int		row;
	int		i;

	s = ft_strinit('.', map_size * (map_size + 1));
	row = map_size;
	s[((map_size + 1) * row) - 1] = '\0';
	while (--row)
		s[((map_size + 1) * row) - 1] = '\n';
	while (tetrominos->content)
	{
		row = 0;
		i = MINO_SIZE;
		while (i--)
		{
			if ((MINO(tetrominos) >> i) & 0x0001)
				s[(Y(tetrominos) + row) * (map_size + 1) + X(tetrominos) +
				(((MINO_SIZE - 1) - i) % 4)] = C(tetrominos);
			if ((MINO_SIZE - i) % 4 == 0)
				++row;
		}
		tetrominos = tetrominos->next;
	}
	ft_putendl(s);
}

/*
**	The place_mino() function first moves the map pointer (temporarily) to the
**	first row that the tetromino piece should be placed. It then loops
**	through the tetromino piece row by row and places that row on the map
**	using the bitwise xor (^) operator. This function can also unplace pieces
**	by calling it again, which is super convenient for backtracking.
**
**	(for more information on the macros used, see the fillit.h file)
*/

static void		place_mino(uint16_t map[], t_list *mino)
{
	int row;

	row = 0;
	map = map + Y(mino);
	while (row < 4)
	{
		*map = *map ^ ROW(row, mino) >> X(mino);
		++row;
		++map;
	}
}

/*
**	The find_spot() function uses macros to easily isolate sections of the
**	board, and goes through various checks to see if/where the given tetromino
**	can fit. This function recursively checks the tetromino piece one row at a
**	time, using bitsize operations to ensure that there is no overlap. This
**	function will set the x and y variables inside of the t_mino struct for a
**	particular piece.
**
**	(for more information on the macros used, see the fillit.h file)
*/

static int		find_spot(uint16_t map[], int map_size, t_list *mino, int row)
{
	if (!map || (((Y(mino) + row) >= map_size) && (ROW(row, mino) > 0)))
		return (-1);
	if (LAST(mino) == CORD(mino, map_size))
		++X(mino);
	if (X(mino) >= (map_size - 3) &&
		(MINO(mino) & (0x1111 << ((X(mino) - (map_size - 3))))))
	{
		++Y(mino);
		X(mino) = 0;
		return (find_spot(map, map_size, mino, 0));
	}
	if (row == 0)
	{
		if (XOROR(*(map + Y(mino)), (ROW(row, mino) >> X(mino))))
			if (find_spot(map + 1, map_size, mino, row + 1))
				return (find_spot(map + 1, map_size, mino, row + 1));
		++X(mino);
		return (find_spot(map, map_size, mino, row));
	}
	if (row < 3 && XOROR(*(map + Y(mino)), (ROW(row, mino) >> X(mino))))
		return (find_spot(map + 1, map_size, mino, row + 1));
	else
		return (XOROR(*(map + Y(mino)), (ROW(row, mino) >> X(mino))));
}

/*
**	The fill_map() function is a recursive backtracking algorithm. It attempts
**	to find a spot for each piece and places that piece in the position
**	found. It will then call the function on the next piece and try to find a
**	place for it. If fill_map() with the next piece returns 0, meaning that it
**	couldn't find a spot for it, the current piece is unplaced and moved to the
**	first open spot it can find. fill_map() then tries again with the next
**	piece. This will recursively handle placing all the pieces, and once the
**	board is complete it will return 1 all the way through the stack and
**	fill_map() will return to map_main().
**
**	NOTE: The place_mino() function uses the bitwise operator xor (^) to place
**	pieces on the board, so by calling it a second time with the same
**	parameters, it will act as an UNplace function as well.
*/

static int		fill_map(uint16_t map[], int map_size, t_list *tetrominos)
{
	int		fit;

	if (!tetrominos->content)
		return (1);
	LAST(tetrominos) = -1;
	X(tetrominos) = 0;
	Y(tetrominos) = 0;
	fit = find_spot(map, map_size, tetrominos, 0);
	while (fit == 1)
	{
		LAST(tetrominos) = CORD(tetrominos, map_size);
		place_mino(map, tetrominos);
		if (fill_map(map, map_size, tetrominos->next))
			return (1);
		place_mino(map, tetrominos);
		fit = find_spot(map, map_size, tetrominos, 0);
	}
	return (0);
}

/*
**	The map_main() function finds the smallest reasonable board size based on
**	the number of tetrominos in the linked list, creates a board of that size
**	and then calls the backtracking algorithm fill_map(). If it sucessfully
**	places all the pieces then it prints the board, or else it prints error
*/

void			map_main(t_list *tetrominos)
{
	uint16_t	map[MAX_BOARD_SIZE];
	int			count;
	int			map_size;

	ft_bzero(map, sizeof(uint16_t) * MAX_BOARD_SIZE);
	count = ft_lstlen(tetrominos);
	map_size = 2;
	while (map_size * map_size < count * 4)
		++map_size;
	while (map_size <= MAX_BOARD_SIZE)
	{
		if (!fill_map(map, map_size, tetrominos))
			++map_size;
		else
			break ;
	}
	if (map_size > MAX_BOARD_SIZE)
		ft_putendl("error");
	else
		print_map(tetrominos, map_size);
}
