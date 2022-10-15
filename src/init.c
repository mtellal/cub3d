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
	/* double x = j * GRID;
	double y = i * GRID; */

	img->triangle.ipos.h = i * GRID;
	img->triangle.ipos.l = j * GRID;

///////////////////////////////////////////////////////////////////

	img->triangle.no.x = j * GRID + GRID * 0.4;
	img->triangle.no.y = i * GRID + GRID * 0.2;

	img->triangle.ne.x = j * GRID + GRID * 0.6;
	img->triangle.ne.y = i * GRID + GRID * 0.2;

	img->triangle.so.x = j * GRID + GRID * 0.2;
	img->triangle.so.y = i * GRID + GRID * 0.8;

	img->triangle.se.x = j * GRID + GRID * 0.8;
	img->triangle.se.y = i * GRID + GRID * 0.8;

////////////////////////////////////////////////////////////////////

	img->triangle.a.x = j * GRID + GRID / 2;
	img->triangle.a.y = i * GRID + GRID / 3;

	img->triangle.b.x = j * GRID + GRID / 3;
	img->triangle.b.y = i * GRID + GRID * 2 / 3;

	img->triangle.c.x = j * GRID + GRID * 2 / 3;
	img->triangle.c.y = i * GRID + GRID * 2 / 3;

	img->triangle.milieu.x = j * GRID + GRID / 2;
	img->triangle.milieu.y = i * GRID + GRID / 2;

	img->triangle.color = PLAYERCOLOR;

//////////////////////////////////////////////////////////////////////


	img->ray.b.x = img->triangle.a.x;
	img->ray.b.y = img->triangle.a.y;

	img->ray.c.x = img->triangle.a.x;
	img->ray.c.y = img->triangle.a.y;

	img->ray.a.x = img->triangle.milieu.x;
	img->ray.a.y = img->triangle.milieu.y;

	img->ray.ipos.h = img->triangle.ipos.h - GRID;
	img->ray.ipos.l = img->triangle.ipos.l;

	img->ray.color = 0x00FFF0FF;

	rotatePoint(deg2rad(ANGLE / 2), &img->ray.b.x, &img->ray.b.y, img->triangle.milieu);
	rrotatePoint(deg2rad(ANGLE / 2), &img->ray.c.x, &img->ray.c.y, img->triangle.milieu);
}

/* affiche les murs et init le triangle lorsque N est trouve
 * note: les murs sont affiches qu'une seul fois, les events modifient uniquement le triangle 
*/

void	fillWalls(t_frame *img2D, char map[MHEIGHT][MLENGTH])
{
	int i = 0;
	int j = 0;
	t_wall	w;

	w.size = GRID;
	w.color = WALLCOLOR;

	while (i < 14)
	{
		j = 0;
		while (j < 33)
		{
			if (map[i][j] == '1')
				draw_wall(img2D, w, i * w.size, j * w.size);
			else if (map[i][j] == 'N')
			{
				initTriangle(img2D, i, j);
				put_pixel(img2D, img2D->triangle.milieu.y, img2D->triangle.milieu.x, PLAYERCOLOR);
				draw_triangle(img2D, img2D->triangle, img2D->triangle.color);
 			}
			j++;
		}
		i++;
	}
}

void	initImg2D(t_data *data, t_frame *img2D)
{
	//img2D->mlx = data->mlx;
	//img->window = mlx_new_window(img->mlx, LENGTH, HEIGHT, "cub3d");
	img2D->img = mlx_new_image(data->mlx, LENGTH, HEIGHT);
	img2D->addr = mlx_get_data_addr(img2D->img, &img2D->bpp, &img2D->length, &img2D->endian);
	img2D->move = 0;
}

void	initImg3D(t_data *data, t_frame *img2D, t_frame *img3D)
{
	//img3D->mlx = data->mlx;
	img3D->window = mlx_new_window(data->mlx, LENGTH2, HEIGHT2, "cub3d");
	img3D->img = mlx_new_image(data->mlx, LENGTH2, HEIGHT2);
	img3D->addr = mlx_get_data_addr(img3D->img, &img3D->bpp, &img3D->length, &img3D->endian);

	/////////
    castRays(data, img2D, img3D, img2D->triangle.milieu, LENGTH, 0x00FFFFFF, 1);
	draw_triangle(img2D, img2D->triangle, img2D->triangle.color);
	miniMap(&data->img2D, &data->img3D);
	mlx_put_image_to_window(data->mlx, data->img3D.window, data->img3D.img, 0, 0);
}

void	initTexture(void *mlx, t_texture *texture)
{

	texture->wall.img = mlx_xpm_file_to_image(mlx, PATHWALL, &texture->wall.width, &texture->wall.height);
	texture->wall.addr = mlx_get_data_addr(texture->wall.img, &texture->wall.bpp, &texture->wall.length, &texture->wall.endian);
	
	texture->cieling.img = mlx_xpm_file_to_image(mlx, PATHCIELING, &texture->cieling.width, &texture->cieling.height);
	texture->cieling.addr = mlx_get_data_addr(texture->cieling.img, &texture->cieling.bpp, 
	&texture->cieling.length, &texture->cieling.endian);

	texture->floor.img = mlx_xpm_file_to_image(mlx, PATHFLOOR, &texture->floor.width, &texture->floor.height);
	texture->floor.addr = mlx_get_data_addr(texture->floor.img, &texture->floor.bpp, 
	&texture->floor.length, &texture->floor.endian);


}

void	init(t_data *data)
{
	data->mlx = mlx_init();
	initImg2D(data, &data->img2D);
	fillWalls(&data->img2D, map);
	initTexture(data->mlx, &data->texture);
	initImg3D(data, &data->img2D, &data->img3D);
}
