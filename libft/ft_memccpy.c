/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:13:44 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/08 18:57:14 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (n--)
	{
		*d++ = *s++;
		if ((*d) == (char)c)
			return (d);
	}
	return (NULL);
}
