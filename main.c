/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:48:31 by abarnett          #+#    #+#             */
/*   Updated: 2018/06/26 11:49:32 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <fcntl.h>

t_mino		*new_mino(char ch, uint16_t bits)
{
	t_mino	*newmino;

	newmino = (t_mino *)ft_memalloc(sizeof(t_mino));
	if (!newmino)
		return (0);
	newmino->c = ch;
	newmino->mino = bits;
	newmino->x = 0;
	newmino->y = 0;
	newmino->last = -1;
	return (newmino);
}

uint16_t	validate(uint16_t mino)
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

uint16_t	get_mino(char *buf)
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
			mino = mino | (1 << (15 - (i - (i / 5))));
		else if (buf[i] != '.' && buf[i] != '\n')
			return (0);
		else if (buf[i] == '\n' && ((i + 1) % 5 != 0))
			return (0);
		++i;
	}
	return ((count != 4 || i != 20) ? 0 : validate(mino));
}

t_list		*create_list(int fd, char *buf, int *prev_read)
{
	t_list		*head;
	t_list		*cur;
	int			count;
	uint16_t	bits;
	int			bytes;

	head = ft_lstnew(0, 0);
	if (!head)
		return (0);
	cur = head;
	count = 0;
	while (count < 26 && (bytes = read(fd, buf, MINO_SIZE)) != 0)
	{
		*prev_read = bytes;
		buf[MINO_SIZE - 1] = (buf[20] == '\n' ? '\0' : 0);
		bits = get_mino(buf);
		cur->content = new_mino('A' + count, bits);
		if (!cur->content || !bits)
			return (0);
		++count;
		cur->content_size = sizeof(cur->content);
		cur->next = ft_lstnew(0, 0);
		cur = cur->next;
	}
	return (head);
}

int			main(int argc, char **argv)
{
	char	*buf;
	int		fd;
	t_list	*head;
	int		prev_read;

	if (argc != 2)
	{
		ft_putendl("usage: ./fillit <file>");
		return (0);
	}
	buf = ft_strnew(MINO_SIZE + 1);
	prev_read = 0;
	fd = open(argv[1], O_RDONLY);
	head = create_list(fd, buf, &prev_read);
	close(fd);
	if (!head || !head->content || prev_read != 20)
	{
		ft_putendl("error");
		return (0);
	}
	map_main(head);
	return (0);
}
