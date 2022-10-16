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

void	displayCieling(t_frame *img, t_texture *texture, int posx, int posy, int l)
{
	t_img *cieling = &texture->cieling;
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

void	displayWall(t_frame *img, t_texture *texture, t_coor posImg, int h, int l, t_coor poswall, 
double ratio_imgwall_strip_h)
{
	t_img	*wall;
	int		wallpixel;
	int		i;
	int		j;
	
	wall = &texture->wall;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			wallpixel = *(int *)(wall->addr + (int)poswall.x * wall->length + 
						(int)(i * ratio_imgwall_strip_h) * wall->length + 
						(int)poswall.y * (wall->bpp / 8) + 
						j * (wall->bpp / 8));
				put_pixel(img, (int)posImg.x + i, (int)posImg.y + j, wallpixel);
			j++;
		}
		i++;
	}
}

//	display une bande de pixel correspondant a un rayon
//	bande qui comment ce la posx et fait h de haut et l de large

void	displayRay(t_frame *img, t_coor posImg, t_coor_map wall, t_texture *texture, t_coor poswall, 
		double ratio_imgwall_strip_h)
{
	// plafond	
	displayCieling(img, texture, posImg.x, posImg.y, wall.l);

	// mur
	displayWall(img, texture, posImg, wall.h, wall.l, poswall, ratio_imgwall_strip_h);

	displayFloor(img, (int)posImg.x + wall.h, (int)posImg.y, wall.l);
}

void	displayRays(t_frame *img, double length, double nbrays, int i, t_texture *texture, int poslwall)
{
	t_coor		posImg;
	t_coor		posWall;
	t_coor_map	wall;
	double		distpp;
	double		scale_y;

	posWall.x = 0;
	posWall.y = poslwall * texture->wall.width / GRID;
	distpp = ((double)HEIGHT2 / 2) / tan(deg2rad(30));
	wall.l = (double)LENGTH2 / nbrays;
	wall.h = ((double)GRID / length) * distpp;
	posImg.x = ((double)HEIGHT2 / 2) - (wall.h / 2);
	posImg.y = (int)wall.l * i;
	scale_y = (double)(texture->wall.height) / wall.h;
	if (posImg.x < 0)
		posImg.x = 0;
	if (wall.h > (double)HEIGHT2)
	{
		posWall.x = ((int)wall.h - (double)HEIGHT2) / 2 * scale_y;
		wall.h = (double)HEIGHT2 - 1;
	}
	displayRay(img, posImg, wall, texture, posWall, scale_y);
}

void	displayCastRays(t_frame *img, t_ray **rays, t_texture *texture)
{
	t_ray	*_ray;

	(void)_ray;
	(void)img;
	(void)rays;
	(void)texture;

	int i = 0;
	while (i < NBRAYS)
	{
		_ray = rays[i];
		/* if (_ray && _ray->length && _ray->posstripwall)
		{
			ft_putnbr_fd(_ray->length, 1);
			ft_putstr_fd("\n", 1);
		} */
		if (_ray)
			displayRays(img, _ray->length, NBRAYS, i, texture, _ray->posstripwall);
		i++;
	}

}
