/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:22:58 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/08 18:52:40 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc2(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (!(tmp))
		return (NULL);
	ft_bzero(tmp, size);
	return (tmp);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)ft_memalloc2(size * nmemb);
	if (!(ptr))
		return (NULL);
	return (ptr);
}
