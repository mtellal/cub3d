/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayRays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:37:13 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/14 10:37:21 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	displayCieling(t_frame *img, t_img *cieling, int posx, int posy, int l)
{
	int pixel;

	double himg = HEIGHT2;
	double limg = LENGTH2;


	double scale_h = (double)cieling->height / himg;
	double scale_l = (double)cieling->width / limg;

	int i = 0;
	int j;

	while (i < posx)
	{
		j = 0;
		while (j < l)
		{
			pixel = *(int *)(cieling->addr + 
						(int)(cieling->height / 5) * cieling->length + 
						(int)(i * scale_h) * cieling->length + 
						(int)(posy * scale_l) * (cieling->bpp / 8) +
						(int)(j * scale_l) * (cieling->bpp / 8));

			put_pixel(img, i, posy + j, pixel);
			j++;
		}
		i++;
	}
}

void	displayFloor(t_frame *img, int posx, int posy, int l)
{
	int i = posx;
	int j = 0;

	while (i < HEIGHT2)
	{
		j = 0;
		while (j < l)
		{
			put_pixel(img, i, posy + j, FLOORCOLOR);
			j++;
		}
		i++;
	}
}

void	displayStripWall(t_frame *img, t_img *wall, t_coor posImg, int h, int l, t_coor poswall, 
double ratio_imgwall_strip_h)
{
	int		wallpixel;
	int		i;
	int		j;
	
	(void)wallpixel;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			wallpixel = *(int *)(wall->addr + (int)poswall.y * wall->length + 
						(int)(i * ratio_imgwall_strip_h) * wall->length + 
						(int)poswall.x * (wall->bpp / 8) + 
						j * (wall->bpp / 8));
				put_pixel(img, (int)posImg.y + i, (int)posImg.x + j, wallpixel);
			j++;
		}
		i++;
	}
}

void	displayWall(t_frame *img, t_img *texture, t_coor posWallImg3d, t_coor_map wallImg3D, int posStripWallImg2D)
{
		t_coor		posWall;
		double 		scale_y;

		posWall.y = 0;
		posWall.x = posStripWallImg2D * texture->width / (double)(GRID);
		scale_y = (double)(texture->height) / wallImg3D.h;

		(void)posWall;
		(void)scale_y;
		(void)img;


		if (posWallImg3d.y < 0)
			posWallImg3d.y = 0;
		if (wallImg3D.h >= (double)(HEIGHT2))
		{
			posWall.y = (wallImg3D.h - (double)HEIGHT2) / 2 * scale_y;
			wallImg3D.h = (double)HEIGHT2 - 1;
		}

		displayStripWall(img, texture, posWallImg3d, wallImg3D.h, wallImg3D.l, posWall, scale_y);
		//displayRay(img, posWallImg3d, wallImg3D, texture, posWall, scale_y);
}

void	displayCastRays(t_frame *img, t_ray **rays, t_texture *texture)
{
	t_ray	*_ray;
	double		distpp;
	t_coor		posWallImg3d;
	t_coor_map	wallImg3D;
	int			i;

	distpp = ((double)HEIGHT2 / 2) / tan(deg2rad(30));
	wallImg3D.l = (double)(LENGTH2) / (double)(NBRAYS);
	i = 0;
	while (i < NBRAYS)
	{
		_ray = rays[i];
		if (_ray)
		{
			wallImg3D.h = ((double)GRID / _ray->length) * distpp;
			posWallImg3d.x = wallImg3D.l * i;
			posWallImg3d.y = ((double)HEIGHT2 / 2) - (wallImg3D.h / 2);
			displayCieling(img, &texture->cieling, posWallImg3d.y, posWallImg3d.x, wallImg3D.l);

			if (_ray->walldirection == NORD)
				displayWall(img, &texture->walln, posWallImg3d, wallImg3D, _ray->posstripwall);
			else if (_ray->walldirection == SUD)
				displayWall(img, &texture->walls, posWallImg3d, wallImg3D, _ray->posstripwall);
			else if (_ray->walldirection == OUEST)
				displayWall(img, &texture->wallo, posWallImg3d, wallImg3D, _ray->posstripwall);
			else if (_ray->walldirection == EST)
				displayWall(img, &texture->walle, posWallImg3d, wallImg3D, _ray->posstripwall);

			displayFloor(img, wallImg3D.h + posWallImg3d.y, posWallImg3d.x, wallImg3D.l);
		}
		i++;
	}
}
