/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 10:14:30 by abarnett          #+#    #+#             */
/*   Updated: 2018/06/06 16:49:23 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_numlen(long num)
{
	int	length;

	length = 1;
	if (num < 0)
	{
		num *= -1;
		++length;
	}
	while (num >= 10)
	{
		num /= 10;
		++length;
	}
	return (length);
}