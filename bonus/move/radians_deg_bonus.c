/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radians_deg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:34:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:34:53 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180));
}

double	rad2deg(double radians)
{
	return (radians * (180 / M_PI));
}
