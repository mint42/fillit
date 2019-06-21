/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:48:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/06/20 20:13:54 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "ft_put.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_list.h"
#include <unistd.h>
#include <fcntl.h>

/*
**	The new_mino() function allocates for a new t_mino struct pointer and
**	initializes it with information about the tetromino.
*/

static t_mino		*new_mino(char c, uint16_t bits)
{
	t_mino	*newmino;

	newmino = (t_mino *)ft_memalloc(sizeof(t_mino));
	if (!newmino)
		return (0);
	newmino->c = c;
	newmino->mino = bits;
	newmino->x = 0;
	newmino->y = 0;
	newmino->last = -1;
	return (newmino);
}

/*
**	The validate() function first shifts the leading 0's out of the piece so
**	that the tetromino is as top-left as it can be. It does this in the first
**	two while loops. First looping while a whole top row is insignificant, and
**	then looping while the left column is insignificant. The tetromino is
**	bitwise anded (&) with these two values respectively.
**
**	The second part of the validation process is done with a series of bitwise
**	ands (&) against paritially valid tetromino configurations to validate
**	a piece by process of elimination.
**
**	(For visualizations on all valid tetrominos, see the README.md)
**	A visualization for the partial pieces are as follows:
*/

/*
**	FIRST PART
**
**	0xF000 :
**		1 1 1 1
**		0 0 0 0
**		0 0 0 0
**		0 0 0 0
**
**	0x8888 :
**		1 0 0 0
**		1 0 0 0
**		1 0 0 0
**		1 0 0 0
**
**	SECOND PART
**
**	0xE000 :
**		1 1 1 0
**		0 0 0 0
**		0 0 0 0
**		0 0 0 0
**
**	0x1E00 :
**		0 0 0 1
**		1 1 1 0
**		0 0 0 0
**		0 0 0 0
**
**	0x8880 :
**		1 0 0 0
**		1 0 0 0
**		1 0 0 0
**		0 0 0 0
**
**	0x4448 :
**		0 1 0 0
**		0 1 0 0
**		0 1 0 0
**		1 0 0 0
**
**	0x4C00 :
**		0 1 0 0
**		1 1 0 0
**		0 0 0 0
**		0 0 0 0
**
**	0xA2C0 :
**		1 0 1 0
**		0 0 1 0
**		1 1 0 0
**		0 0 0 0
**
**	0x8400 :
**		1 0 0 0
**		0 1 0 0
**		0 0 0 0
**		0 0 0 0
**
**	0x8640 :
**		1 0 0 0
**		0 1 1 0
**		0 1 0 0
**		0 0 0 0
**
**	0x31BF :
**		0 0 1 1
**		0 0 0 1
**		1 0 1 1
**		1 1 1 1
**
**	0x44C0 :
**		0 1 0 0
**		0 1 0 0
**		1 1 0 0
**		0 0 0 0
**
**	0x2E00 :
**		0 0 1 0
**		1 1 1 0
**		0 0 0 0
**		0 0 0 0
*/

static uint16_t		validate(uint16_t mino)
{
	while (!(mino & 0xF000))
		mino = mino << 4;
	while (!(mino & 0x8888))
		mino = mino << 1;
	if ((mino & 0xE000) == 0xE000)
		return ((mino & 0x1E00) ? mino : 0);
	if ((mino & 0x8880) == 0x8880)
		return ((mino & 0x4448) ? mino : 0);
	if ((mino & 0x4C00) == 0x4C00)
		return ((mino & 0xA2C0) ? mino : 0);
	if (((mino & 0x8400) == 0x8400) && (mino != 0x8640))
		return ((mino & 0x31BF) ? 0 : mino);
	return ((mino == 0x44C0 || mino == 0x2E00) ? mino : 0);
}

/*
**	The get_mino() function loops through a tetromino piece one byte at a time
**	and bit encodes a uint16_t with the same pattern found in buf. It also
**	validates that there are the correct number of #'s and .'s found in piece.
**	Once that's finished and the piece is so far valid, it sends the bits to
**	the validate() function which checks if the bits are in a valid tetromino
**	configuration.
*/

static uint16_t		get_mino(char *buf)
{
	uint16_t	mino;
	int			i;
	int			count;

	mino = 0;
	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == '#' && ++count)
			mino = mino | (1 << ((MINO_SIZE - 1) - (i - (i / 5))));
		else if (buf[i] != '.' && buf[i] != '\n')
			return (0);
		else if (buf[i] == '\n' && ((i + 1) % 5 != 0))
			return (0);
		++i;
	}
	return ((count != 4 || i != (BUFF_SIZE - 1)) ? 0 : validate(mino));
}

/*
**	The create_list() function takes the given file descriptor, reads through
**	the file one BUFF_SIZE at a time (BUFF_SIZE is equivilent to 1 tetromino
**	piece - 21 bytes), and then validates the piece before adding it to the
**	linked list. This will loop until there is an error while validating a
**	tetromino or until the number of tetrominos is larger than MAX_TETROMINOS,
**	which is 26.
*/

static t_list		*create_list(int fd, char *buf, int *prev_read)
{
	t_list		*tetrominos;
	t_list		*cur;
	int			count;
	uint16_t	bits;
	int			bytes;

	tetrominos = ft_lstnew(0, 0);
	if (!tetrominos)
		return (0);
	cur = tetrominos;
	count = 0;
	while (count < MAX_TETROMINOS && (bytes = read(fd, buf, BUFF_SIZE)) != 0)
	{
		*prev_read = bytes;
		buf[BUFF_SIZE - 1] = (buf[BUFF_SIZE - 1] == '\n' ? '\0' : 0);
		bits = get_mino(buf);
		cur->content = new_mino('A' + count, bits);
		if (!cur->content || !bits)
			return (0);
		++count;
		cur->content_size = sizeof(cur->content);
		cur->next = ft_lstnew(0, 0);
		cur = cur->next;
	}
	return (tetrominos);
}

/*
**	The main() function opens the file of tetrominos that was given on the
**	command line, calls create_list() to make a linked list of all the pieces,
**	and then calls map_main() which implements the backtracking algorithm that
**	will organize the pieces into the smallest possible square and print that
**	map to stdout
*/

int					main(int argc, char **argv)
{
	char		buf[BUFF_SIZE + 1];
	t_list		*tetrominos;
	int			fd;
	int			prev_read;

	if (argc != 2)
	{
		ft_putendl("usage: ./fillit file");
		return (0);
	}
	prev_read = 0;
	fd = open(argv[1], O_RDONLY);
	tetrominos = create_list(fd, buf, &prev_read);
	close(fd);
	if (!tetrominos || !tetrominos->content || prev_read != 20)
	{
		ft_putendl("error");
		return (0);
	}
	map_main(tetrominos);
	return (0);
}
