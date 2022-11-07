/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_a_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:46:21 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 11:23:22 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coor	set_rayxa(t_ray *sray, t_coor coor_r, t_coor origine)
{
	if (coor_r.y < origine.y)
		sray->walldirection = NORD;
	else
		sray->walldirection = SUD;
	sray->posstripwall = (int)coor_r.x % GRID;
	return (coor_r);
}

t_coor	set_rayya(t_ray *sray, t_coor coor_r, t_coor origine)
{
	if (coor_r.x < origine.x)
		sray->walldirection = OUEST;
	else
		sray->walldirection = EST;
	sray->posstripwall = (int)coor_r.y % GRID;
	return (coor_r);
}

t_coor	castaray(t_data *d, t_coor p, double angle, t_ray *r)
{
	t_coor	origine;
	t_coor	pointxa;
	t_coor	pointya;

	origine = d->p.pos;
	pointxa = hor_cast(d, p, origine, angle);
	pointya = vert_cast(d, p, origine, angle);
	if (getlengthray(pointxa, origine, angle)
		< getlengthray(pointya, origine, angle))
		return (set_rayxa(r, pointxa, origine));
	else
		return (set_rayya(r, pointya, origine));
}
