/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:48:31 by abarnett          #+#    #+#             */
/*   Updated: 2018/06/22 12:25:04 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

void	print_map(t_list *list, int size)
{
	char	*s;
	int		row;
	int		i;

	s = ft_strinit(sizeof(char) * size * (size + 1), '.');
	row = size;
	s[((size + 1) * row) - 1] = '\0';
	while (--row)
		s[((size + 1) * row) - 1] = '\n';
	while (list->content)
	{
		row = 0;
		i = 16;
		while (i--)
		{
			if ((BITS(list) >> i) & 0x0001)
				s[(Y(list) + row) * (size + 1) + X(list) +
				((15 - i) % 4)] = CHAR(list);
			if ((16 - i) % 4 == 0)
				++row;
		}
		list = list->next;
	}
	ft_putendl(s);
}

void	place_mino(uint16_t map[], t_list *mino)
{
	int i;

	i = -1;
	map += Y(mino);
	while (++i < 4)
		*map++ ^= R(i, mino) >> X(mino);
}

int		find_spot(uint16_t map[], int size, t_list *mino, int row)
{
	if (!map || (((Y(mino) + row) >= size) && (R(row, mino) > 0)))
		return (-1);
	if (LAST(mino) == CORD(mino, size))
		++X(mino);
	if (X(mino) >= (size - 3) &&
		(BITS(mino) & (0x1111 << ((X(mino) - (size - 3))))))
	{
		++Y(mino);
		X(mino) = 0;
		return (find_spot(map, size, mino, 0));
	}
	if (row == 0)
	{
		if (XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))))
			if (find_spot(map + 1, size, mino, row + 1))
				return (find_spot(map + 1, size, mino, row + 1));
		++X(mino);
		return (find_spot(map, size, mino, row));
	}
	if (row < 3 && XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))))
		return (find_spot(map + 1, size, mino, row + 1));
	else
		return (XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))));
}

int		fill_map(uint16_t map[], int size, t_list *cur)
{
	int	fit;

	if (!cur->content)
		return (1);
	LAST(cur) = -1;
	X(cur) = 0;
	Y(cur) = 0;
	fit = find_spot(map, size, cur, 0);
	while (fit == 1)
	{
		LAST(cur) = CORD(cur, size);
		place_mino(map, cur);
		if (fill_map(map, size, cur->next))
			return (1);
		place_mino(map, cur);
		fit = find_spot(map, size, cur, 0);
	}
	return (0);
}

void	map_main(t_list *head)
{
	uint16_t	map[16];
	int			count;
	int			size;

	ft_bzero(map, sizeof(uint16_t) * 16);
	count = ft_lstlen(head);
	size = 2;
	while (size * size < count * 4)
		++size;
	while (size <= 16)
	{
		if (!fill_map(map, size, head))
			++size;
		else
			break ;
	}
	if (size > 16)
		ft_putendl("error");
	print_map(head, size);
}
