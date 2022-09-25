/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:17:02 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/20 09:17:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	verifie si le masque est non nul, alors une touche est presse
 *	efface le triangle
 *	call les functions moveX correspondant aux touches pressees, peut etre en meme temps
 *	display le triangle et push l'image dans la fenetre
 */


void	draw_line(t_frame *img,  t_coor point, t_coor origine, t_coor *ray, int color)
{
	double diff_x;
	double diff_y;
	double steps;

	diff_x = point.x - origine.x;
	diff_y = point.y - origine.y;

	double abs_x;
	double abs_y;

	abs_x = diff_x;
	abs_y = diff_y;

	if (abs_x < 0)
		abs_x *= -1;
	if (abs_y < 0)
		abs_y *= -1;

	steps = abs_x > abs_y ? abs_x : abs_y;
	
	double xinc;
	double yinc;

	xinc = diff_x / steps;
	yinc = diff_y / steps;

	double x = origine.x;
	double y = origine.y;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		put_pixel(img, y, x, color);
		y += yinc;
		x += xinc;
	}	 
	if (ray)
	{
		ray->x = x;
		ray->y = y;
	}
}


void	castRays(t_frame *img, t_frame *img2, t_coor origine, int nbrays)
{
	t_coor b2;
	t_coor c2;

	(void)img2;
	draw_line(img, img->ray.b, origine, &b2, 0x00FFFFFF);
	draw_line(img, img->ray.c, origine, &c2, 0x00FFFFFF);

	double v;
	double distance = 0;

	v = sqrt(pow(origine.y - b2.y, 2) + pow(origine.x - b2.x, 2));
	distance += v * sin(deg2rad(ANGLE));
	v = sqrt(pow(origine.y - c2.y, 2) + pow(origine.x - c2.x, 2));
	distance += v * sin(deg2rad(ANGLE));

	double angleinc = (ANGLE * 2) / nbrays;
	int i = 0;
	t_coor bx;

	bx.x = b2.x;
	bx.y = b2.y;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bx.x, &bx.y, img->triangle.milieu);
		draw_line(img, bx, origine, NULL, 0x00FFFFFF);
		i++;
	}
}


void	erasecastRays(t_frame *img, t_frame *img2, t_coor origine, int nbrays)
{
	t_coor b2;
	t_coor c2;

	(void)img2;
	draw_line(img, img->ray.b, origine, &b2, 0);
	draw_line(img, img->ray.c, origine, &c2, 0);

	double v;
	double distance = 0;

	v = sqrt(pow(origine.y - b2.y, 2) + pow(origine.x - b2.x, 2));
	distance += v * sin(deg2rad(ANGLE));
	v = sqrt(pow(origine.y - c2.y, 2) + pow(origine.x - c2.x, 2));
	distance += v * sin(deg2rad(ANGLE));

	double angleinc = (ANGLE * 2) / nbrays;
	int i = 0;
	t_coor bx;

	bx.x = b2.x;
	bx.y = b2.y;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bx.x, &bx.y, img->triangle.milieu);
		draw_line(img, bx, origine, NULL, 0);
		i++;
	}
}



void    move(t_data *data)
{
	t_frame *img = &data->img;

    if (!img->move)
    		return ;
	draw_line(img, img->ray.b, img->triangle.a, NULL, 0);
	draw_line(img, img->ray.c, img->triangle.a, NULL, 0);
	erasecastRays(&data->img, &data->img2, img->triangle.a, 10);
   	draw_triangle(img, img->triangle, 0);
	/* erase_line(img, img->ray.b, img->triangle.a);
	erase_line(img, img->ray.c, img->triangle.a); */
    if (img->move & U)
            moveUP(img);
    if (img->move & D)
            moveDOWN(img);
    if (img->move & R)
            moveRIGHT(img);
    if (img->move & L)
            moveLEFT(img);
    if (img->move & VR)
            moveVRIGHT(img);
    if (img->move & VL)
            moveVLEFT(img);
	//draw_triangle2(img, img->ray);
	draw_triangle(img, img->triangle, img->triangle.color);
   /*  put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FFFFFF);
	put_pixel(img, img->ray.b.y, img->ray.b.x, 0x00FFFFFF); */
	//put_pixel(img, img->ray.c.y, img->ray.c.x, 0x00FFFFFF);
	//put_pixel(img, img->ray.a.y, img->ray.a.x, 0x00F0FFFF);
	//put_pixel(img, img->ray.ipos.x, img->ray.ipos.y - 50, 0x00FFFFFF);
	castRays(&data->img, &data->img2, img->triangle.a, 10);
    push_frame(img);
} 

