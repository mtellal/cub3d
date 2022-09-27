/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:57:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/23 12:57:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* set les points a, b, c (triangle direction nord avec a en avant)
 * set milieu du triangle, necessaire pour la rotation (origine du plan) 
 * set ipos ou i = ligne dans le tab et j = le pixel de la ligne 
 */

void	initTriangle(t_frame *img, int i, int j)
{
	img->triangle.ipos.h = i * GRID;
	img->triangle.ipos.l = j * GRID;

	img->triangle.a.x = j * GRID + GRID / 2;
	img->triangle.a.y = i * GRID + GRID / 4;

	img->triangle.b.x = j * GRID + GRID / 4;
	img->triangle.b.y = i * GRID + GRID * 0.75;

	img->triangle.c.x = j * GRID + GRID * 0.75;
	img->triangle.c.y = i * GRID + GRID * 0.75;

	img->triangle.milieu.x = j * GRID + GRID / 2;
	img->triangle.milieu.y = i * GRID + GRID * 0.6;

	img->triangle.color = 0x00F50600;
//////////////////////////////////////////////////////////////////////
	/* img->ray.b.x = img->triangle.ipos.l + GRID / 2;
	img->ray.b.y = img->triangle.ipos.h - GRID;

	img->ray.c.x = img->triangle.ipos.l + GRID / 2;
	img->ray.c.y = img->triangle.ipos.h - GRID; */

	img->ray.b.x = img->triangle.a.x;
	img->ray.b.y = img->triangle.a.y;

	img->ray.c.x = img->triangle.a.x;
	img->ray.c.y = img->triangle.a.y;

	img->ray.a.x = img->triangle.milieu.x;
	img->ray.a.y = img->triangle.milieu.y;

	img->ray.ipos.h = img->triangle.ipos.h - GRID;
	img->ray.ipos.l = img->triangle.ipos.l;

	img->ray.color = 0x00FFF0FF;

	rotatePoint(deg2rad(ANGLE), &img->ray.b.x, &img->ray.b.y, img->triangle.milieu);
	rrotatePoint(deg2rad(ANGLE), &img->ray.c.x, &img->ray.c.y, img->triangle.milieu);
}

/* affiche les murs et init le triangle lorsque N est trouve
 * note: les murs sont affiches qu'une seul fois, les events modifient uniquement le triangle 
*/

void	fillWalls(t_frame *img, char map[14][35])
{
	int i = 0;
	int j = 0;
	t_wall	w;

	w.size = GRID;
	w.color = 0x00B0FF00;

	while (i < 14)
	{
		j = 0;
		while (j < 35)
		{
			if (map[i][j] == '1')
				draw_wall(img, w, i * w.size, j * w.size);
			else if (map[i][j] == 'N')
			{
				initTriangle(img, i, j);
				put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FF5689);
				draw_triangle(img, img->triangle, img->triangle.color);
 			}
			j++;
		}
		i++;
	}
}

void	initImg(t_frame *img)
{
	img->mlx = mlx_init();
	img->window = mlx_new_window(img->mlx, LENGTH * GRID, HEIGHT * GRID, "cub3d");
	img->img = mlx_new_image(img->mlx, LENGTH * GRID, HEIGHT * GRID);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, &img->endian);
	img->move = 0;
}

void	initImg3D(t_frame *img)
{
	img->mlx = mlx_init();
	img->window = mlx_new_window(img->mlx, 2 * LENGTH * GRID, 2 * HEIGHT * GRID, "cub3d");
	img->img = mlx_new_image(img->mlx, 2 * LENGTH * GRID, 2 * HEIGHT * GRID);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, &img->endian);
	img->move = 0;
}

void	init(t_data *data)
{
	initImg(&data->img);
	initImg3D(&data->img2);
	data->img2.mlx = data->img.mlx;

	fillWalls(&data->img, map);
	
	push_frame(&data->img);
}
