/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initTriangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:05:40 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/19 16:05:46 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initTriangleCollisions(t_frame *img, int i, int j)
{
	img->triangle.no.x = j * GRID + GRID * 0.4;
	img->triangle.no.y = i * GRID + GRID * 0.2;

	img->triangle.ne.x = j * GRID + GRID * 0.6;
	img->triangle.ne.y = i * GRID + GRID * 0.2;

	img->triangle.so.x = j * GRID + GRID * 0.2;
	img->triangle.so.y = i * GRID + GRID * 0.8;

	img->triangle.se.x = j * GRID + GRID * 0.8;
	img->triangle.se.y = i * GRID + GRID * 0.8;
}

void	initTrianglePoints(t_frame *img, int i, int j)
{
	img->triangle.a.x = j * GRID + GRID / 2;
	img->triangle.a.y = i * GRID + GRID / 3;

	img->triangle.b.x = j * GRID + GRID / 3;
	img->triangle.b.y = i * GRID + GRID * 2 / 3;

	img->triangle.c.x = j * GRID + GRID * 2 / 3;
	img->triangle.c.y = i * GRID + GRID * 2 / 3;

	img->triangle.milieu.x = j * GRID + GRID / 2;
	img->triangle.milieu.y = i * GRID + GRID / 2;
}

void	initTriangle(t_frame *img, int i, int j, char c)
{

	img->triangle.ipos.h = i * GRID;
	img->triangle.ipos.l = j * GRID;

	initTriangleCollisions(img, i, j);
	initTrianglePoints(img, i, j);

	if (c == 'S')
		rotateTriangle(&img->triangle, deg2rad(180));
	else if (c == 'E')
		rrotateTriangle(&img->triangle, deg2rad(90));
	else if (c == 'W')
		rotateTriangle(&img->triangle, deg2rad(90));

	img->triangle.color = PLAYERCOLOR;

}