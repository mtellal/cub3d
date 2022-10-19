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

	/* put_pixel(img, triangle.a.y, triangle.a.x ,0x0000FF00);
	put_pixel(img, triangle.b.y, triangle.b.x ,0x00FF00FF);
	put_pixel(img, triangle.c.y, triangle.c.x ,0x00F0F000);
	put_pixel(img, triangle.milieu.y, triangle.milieu.x, 0x00FFFFFF); */

}

/*	display un mur au sein d'une cellule
 *	le mur affiche est plus petit que la cellule d'ou le 0.1/0.9
*/
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

/*	formule mathematique pour trouver si un point est inclus dans un triangle
 *	forumle utilisee pour re/display le triangle avec ou sans rotation
 */

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