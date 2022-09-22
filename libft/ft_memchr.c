/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:56:37 by antbarbi          #+#    #+#             */
/*   Updated: 2019/11/07 20:15:20 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*d;
	unsigned char		ch;

	d = s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*d == ch)
			return ((void *)d);
		d++;
	}
	return (NULL);
}
