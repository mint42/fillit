/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:10:41 by rreedy            #+#    #+#             */
/*   Updated: 2019/04/17 21:41:00 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_mem.h"
#include <stddef.h>

t_list	*ft_lstinit(void *content, size_t content_size)
{
	t_list *node;

	node = (t_list *)ft_memalloc(sizeof(t_list));
	if (!node)
		return (0);
	node->next = 0;
	if (!content)
	{
		node->content = 0;
		node->content_size = 0;
		return (node);
	}
	node->content = content;
	node->content_size = content_size;
	return (node);
}
