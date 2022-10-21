/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:05:17 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 16:20:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moveup(t_data *data, t_frame *img, t_coor dda_inc)
{
	if (checkcoorsquare(data, img->triangle.no, img->triangle.ne, dda_inc))
	{
		dda_inc.x *= GRID * 0.03;
		dda_inc.y *= GRID * 0.03;
		addpixely(&img->triangle, dda_inc.y);
		addpixelx(&img->triangle, dda_inc.x);
	}
}

void	movedown(t_data *data, t_frame *img, t_coor dda_inc)
{
	dda_inc.x *= -1;
	dda_inc.y *= -1;
	if (checkcoorsquare(data, img->triangle.so, img->triangle.se, dda_inc))
	{
		dda_inc.x *= GRID * 0.03;
		dda_inc.y *= GRID * 0.03;
		addpixely(&img->triangle, dda_inc.y);
		addpixelx(&img->triangle, dda_inc.x);
	}
}

void	moverigth(t_data *data, t_frame *img, t_coor dda_inc)
{
	if (checkcoorsquare(data, img->triangle.ne, img->triangle.se, dda_inc))
	{
		dda_inc.x *= GRID * 0.03;
		dda_inc.y *= GRID * 0.03;
		addpixely(&img->triangle, dda_inc.y);
		addpixelx(&img->triangle, dda_inc.x);
	}
}

void	moveleft(t_data *data, t_frame *img, t_coor dda_inc)
{
	dda_inc.x *= -1;
	dda_inc.y *= -1;
	if (checkcoorsquare(data, img->triangle.no, img->triangle.so, dda_inc))
	{
		dda_inc.x *= GRID * 0.03;
		dda_inc.y *= GRID * 0.03;
		addpixely(&img->triangle, dda_inc.y);
		addpixelx(&img->triangle, dda_inc.x);
	}
}
