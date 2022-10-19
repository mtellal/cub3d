/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:08:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/19 16:08:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_pixel(t_frame *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (x * img->length) + y * (img->bpp / 8)) = color;
}

void	draw_triangle(t_frame *img, t_triangle triangle, int color)
{
 	t_coor	point;
	int	i = triangle.ipos.l;
	int	j = triangle.ipos.h;

	while (i < triangle.ipos.l + GRID)
	{
		j = 0;
		while (j < triangle.ipos.h + GRID)
		{
			point.x = i;
			point.y = j;
			if (dansLeTriangle(point, triangle))
				put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_frame *img, int x, int y)
{
	int	i = x;
	int	j = y;

	while (i < GRID + x)
	{
		j = y;
		while (j < GRID + y)
		{
			if (i > GRID * 0.1 + x && i < GRID * 0.9 + x &&
				j > GRID * 0.1 + y && j < GRID * 0.9 + y)
			put_pixel(img, i, j, WALLCOLOR);
			j++;
		}
		i++;
	}
}

float barycentre (t_coor p1, t_coor p2, t_coor p3)
{
    return (float)((p1.x - p3.x) * (p2.y - p3.y)) - (float)((p2.x - p3.x) * (p1.y - p3.y));
}
 
int dansLeTriangle (t_coor pt, t_triangle t)
{
    int b1, b2, b3;
 
	b1 = 0;
	b2 = 0;
	b3 = 0;
    if (barycentre(pt, t.a, t.b) < 0)
		b1 = 1;
	if (barycentre(pt, t.b, t.c) < 0)
		b2 = 1;
	if (barycentre(pt, t.c, t.a) < 0)
		b3 = 1;
 
    return ((b1 == b2) && (b2 == b3));
}