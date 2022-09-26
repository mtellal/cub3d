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

double	abs_value(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}


/*	dda algotirthm applique de origine (milieu du triangle) a point (ray->b/c qui sont la rotation de a +/-45 deg)
 */

void	draw_line(t_frame *img,  t_coor point, t_coor origine, t_coor *ray, int color, int *length)
{
	double diff_x;
	double diff_y;
	double steps;

	diff_x = point.x - origine.x;
	diff_y = point.y - origine.y;

	double abs_x;
	double abs_y;

	abs_x = abs_value(diff_x);
	abs_y = abs_value(diff_y);

	steps = abs_x > abs_y ? abs_x : abs_y;
	
	double xinc;
	double yinc;

	xinc = diff_x / steps;
	yinc = diff_y / steps;

	double x = origine.x;
	double y = origine.y;

	int	l = 0;

	while (map[(int)(y / GRID)][(int)(x / GRID)] != '1' && 
		y >= 0 && y < GRID * HEIGHT && 
		x >= 0 && x < GRID * LENGTH)
	{
		put_pixel(img, y, x, color);
		y += yinc;
		x += xinc;
		l++;
	}	 
	if (ray)
	{
		ray->x = x;
		ray->y = y;
		
	}
	if (length)
		*length = l;

}

void	draw_square(t_frame *img, int h, int l, t_coor_map pos, int color)
{
	int i = 0;
	int j = 0;

	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			put_pixel(img, i + pos.h, j + pos.l, color);
			j++;
		}
		i++;
	}
}

void	castRays(t_frame *img, t_frame *img2, t_coor origine, int nbrays)
{
	t_coor b2;

	(void)img2;
	draw_line(img, img->ray.b, origine, &b2, 0x00FFFFFF, NULL);

	double angleinc = ANGLE * 2 / nbrays;
	int i = 0;

	i = 0;

	t_coor bx;

	bx.x = b2.x;
	bx.y = b2.y;

	/////////////////////////////////////////////////////////////////////////

	double v = sqrt(pow(origine.y - b2.y, 2) + pow(origine.x - b2.x, 2));

	t_coor_map ipos;
	ipos.h = v;
	ipos.l = 0;

	int length = 0;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bx.x, &bx.y, img->triangle.milieu);
		/* ft_putnbr_fd(angleinc * 50, 1);
		ft_putstr_fd(" ", 1); */

		draw_line(img, bx, origine, NULL, 0x00FFFFFF, &length);
		draw_square(img2, HEIGHT * GRID - 2 * ipos.h, ((LENGTH * GRID)) / nbrays, ipos, 0x00FF0F60);
		ipos.h = length;
		ipos.l += ((LENGTH * GRID)) / nbrays;
		i++;
	}
}


void	erasecastRays(t_frame *img, t_frame *img2, t_coor origine, int nbrays)
{
	t_coor b2;

	(void)img2;
	(void)nbrays;
	draw_line(img, img->ray.b, origine, &b2, 0, NULL);

	double angleinc = ANGLE * 2 / nbrays;
	int i = 0;

	i = 0;

	t_coor bx;

	bx.x = b2.x;
	bx.y = b2.y;
	///////////////////////////////////////////

	double v = sqrt(pow(origine.y - b2.y, 2) + pow(origine.x - b2.x, 2));

	t_coor_map ipos;
	ipos.h = v;
	ipos.l = 0;

	int length = 0;

	while (i < nbrays)
	{
		rrotatePoint(deg2rad(angleinc), &bx.x, &bx.y, img->triangle.milieu);

		draw_line(img, bx, origine, NULL, 0, &length);
		draw_square(img2, HEIGHT * GRID - 2 * ipos.h, ((LENGTH * GRID)) / nbrays, ipos, 0);
		ipos.h = length;
		ipos.l += ((LENGTH * GRID)) / nbrays;
		i++;
	}
}



void    move(t_data *data)
{
	t_frame *img = &data->img;

    if (!img->move)
    		return ;
	erasecastRays(&data->img, &data->img2, img->triangle.milieu, 90);
   	draw_triangle(img, img->triangle, 0);
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
   /*  put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FFFFFF);
	put_pixel(img, img->ray.b.y, img->ray.b.x, 0x00FFFFFF);
	put_pixel(img, img->ray.c.y, img->ray.c.x, 0x00FFFFFF);
	put_pixel(img, img->ray.a.y, img->ray.a.x, 0x00F0FFFF); */
	//put_pixel(img, img->ray.ipos.x, img->ray.ipos.y - 50, 0x00FFFFFF);
	castRays(&data->img, &data->img2, img->triangle.milieu, 90);
	draw_triangle(img, img->triangle, img->triangle.color);
    push_frame(img);
	push_frame(&data->img2);
} 

