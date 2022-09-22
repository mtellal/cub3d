/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:42:18 by antbarbi          #+#    #+#             */
/*   Updated: 2019/11/06 19:42:57 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	char		*revd;
	const char	*revs;

	d = (char *)dest;
	s = (const char *)src;
	revd = d + (n - 1);
	revs = s + (n - 1);
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
		while (n--)
			*revd-- = *revs--;
	return (dest);
}
