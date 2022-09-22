/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:37:33 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/08 18:38:45 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_remove(char c, const char *set)
{
	size_t		i;
	size_t		len;

	len = ft_strlen(set);
	i = 0;
	while (i < len)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	size_t			i;
	size_t			len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (set && ft_remove(s1[i], set))
		i++;
	while (set && len > 1 && ft_remove(s1[len - 1], set))
		len--;
	if (i > len)
		str = ft_calloc(1, 1);
	else
		str = ft_substr(s1, i, len - i);
	return (str);
}
