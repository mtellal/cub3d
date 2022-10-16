/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:06:19 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/16 15:06:27 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	correctFishEye(double length, double cumulangle)
{

	return (length * cos(cumulangle));
}

t_ray	**initTabRays(void)
{
	t_ray	**rays;
	int		i;

	i = 0;
	rays = malloc(sizeof(t_ray *) * NBRAYS);
	if (!rays)
		ft_putstr_fd("ERROR RAYS[LENGTH]\n", 1);
	while (i < NBRAYS)
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