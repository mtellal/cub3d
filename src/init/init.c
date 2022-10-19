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

void	fillWalls(t_data *data, t_frame *img2D)
{
	int i = 0;
	int j = 0;

	while (i < img2D->height / GRID)
	{
		j = 0;
		while (j < img2D->width / GRID)
		{
			if (data->map[i][j] == '1')
				draw_wall(img2D, i * GRID, j * GRID);
			else if (data->map[i][j] == 'N')
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
	img2D->img = mlx_new_image(data->mlx, img2D->width, img2D->height);
	img2D->addr = mlx_get_data_addr(img2D->img, &img2D->bpp, &img2D->length, &img2D->endian);
	img2D->move = 0;
}

void	initImg3D(t_data *data, t_frame *img2D, t_frame *img3D)
{
	//img3D->mlx = data->mlx;
	img3D->window = mlx_new_window(data->mlx, img3D->width, img3D->height, "cub3d");
	img3D->img = mlx_new_image(data->mlx, img3D->width, img3D->height);
	img3D->addr = mlx_get_data_addr(img3D->img, &img3D->bpp, &img3D->length, &img3D->endian);

	/////////
    draw_triangle(img2D, img2D->triangle, img2D->triangle.color);
	t_ray **rays = castRays(data);
	displayRays(img3D, img2D->width, rays, &data->texture);
	//miniMap(data, img2D, img3D);
	free_rays(rays, img2D->width);
	mlx_put_image_to_window(data->mlx, img3D->window, img3D->img, 0, 0);
}

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	initTexture(t_data *data, void *mlx, t_texture *texture)
{
	texture->walln.img = mlx_xpm_file_to_image(mlx, data->n_texture, &texture->walln.width, &texture->walln.height);
	texture->walln.addr = mlx_get_data_addr(texture->walln.img, &texture->walln.bpp, 
	&texture->walln.length,&texture->walln.endian);

	texture->walls.img = mlx_xpm_file_to_image(mlx, data->s_texture, &texture->walls.width, &texture->walls.height);
	texture->walls.addr = mlx_get_data_addr(texture->walls.img, &texture->walls.bpp, 
	&texture->walls.length, &texture->walls.endian);

	texture->wallo.img = mlx_xpm_file_to_image(mlx, data->w_texture, &texture->wallo.width, &texture->wallo.height);
	texture->wallo.addr = mlx_get_data_addr(texture->wallo.img, &texture->wallo.bpp, 
	&texture->wallo.length, &texture->wallo.endian);

	texture->walle.img = mlx_xpm_file_to_image(mlx, data->e_texture, &texture->walle.width, &texture->walle.height);
	texture->walle.addr = mlx_get_data_addr(texture->walle.img, &texture->walle.bpp, 
	&texture->walle.length, &texture->walle.endian);

	texture->cieling = 0;
	texture->floor = 0;
}

void	init(t_data *data)
{
	data->rays = NULL;
	data->img2D.height = data->height * GRID;
	data->img2D.width = data->len * GRID;
	data->img3D.height = data->height * GRID2;
	data->img3D.width = data->len * GRID2;
	data->mlx = mlx_init();
	initImg2D(data, &data->img2D);
	fillWalls(data, &data->img2D);
	initTexture(data, data->mlx, &data->texture);
	initImg3D(data, &data->img2D, &data->img3D);
}
