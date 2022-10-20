/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:06:19 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/20 13:15:37 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	correctFishEye(double length, double cumulangle)
{

	return (length * cos(cumulangle));
}

t_ray	**initTabRays(double nbrays)
{
	t_ray	**rays;
	int		i;

	i = 0;
	rays = malloc(sizeof(t_ray *) * nbrays);
	if (!rays)
		ft_putstr_fd("ERROR RAYS[LENGTH]\n", 1);
	while (i < nbrays)
	{
		rays[i] = (t_ray*)malloc(sizeof(t_ray));
		if (!rays[i])
		{
			ft_putstr_fd("ERROR ALLOCATION RAYS[II]\n", 1);
			exit(1);
		}
		i++;
	}
	return (rays);
}