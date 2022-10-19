/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:46:01 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/08 18:41:31 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cpt;
	t_list	*tmp;

	cpt = 0;
	tmp = lst;
	while (tmp)
	{
		cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}
