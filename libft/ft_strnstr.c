/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:36:25 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/08 18:38:23 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		l;

	i = 0;
	if (!(*little))
		return ((char *)big);
	while (big[i] && (size_t)i < len)
	{
		l = 0;
		if (big[i] == little[0])
		{
			while (big[i + l] && big[i + l] == little[l] && little[l]
				&& (size_t)(i + l) < len)
				l++;
			if (little[l] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
