/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:30:40 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/27 18:30:54 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*

	SEE DOCS	http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/04-detection_des_murs
				https://permadi.com/1996/05/ray-casting-tutorial-7/

*/


t_coor	firstIntersectionVertical(t_coor point, t_coor origine, double angle)
{
	t_coor npoint;

	// facing right / left
	if (point.x > origine.x)
		npoint.x = floor(origine.x / GRID) * GRID + GRID;
	else
		npoint.x = floor(origine.x / GRID) * GRID;

	npoint.y = origine.y - (npoint.x - origine.x) * tan(angle);
	return (npoint);
}

t_coor	firstIntersectionHorizontal(t_coor point, t_coor origine, double angle)
{

	t_coor npoint;
	(void)angle;

	//face up / down
	if (point.y < origine.y)
		npoint.y = floor(origine.y / GRID) * GRID;
	else
		npoint.y = floor(origine.y / GRID) * GRID + GRID;
	npoint.x = origine.x + ((origine.y - npoint.y) / tan(angle));
	return (npoint);
}

/////////////////////////////////////////////////////////////////////////////////////////


t_coor	horizontalCast(t_coor point, t_coor origine, double angle)
{
	t_coor pointXA = firstIntersectionHorizontal(point, origine, angle);

	double xstep = (double)GRID / tan(angle);
	double ystep = GRID;

	// facing right
	if (origine.x > point.x && xstep > 0)
		xstep *= -1;
	// facing left
	else if (origine.x < point.x && xstep < 0)
		xstep *= -1;

	// facing down
	if (origine.y > point.y)
		ystep *= -1;

	while (pointXA.x >= 0 && pointXA.x < LENGTH &&
			pointXA.y >= 0 && pointXA.y < HEIGHT)
	{
		if (map[(int)(pointXA.y / GRID)][(int)(pointXA.x / GRID)] == '1' ||
			(ystep < 0 && map[(int)((pointXA.y - 1) / GRID)][(int)(pointXA.x / GRID)] == '1'))
		{
			break ;
		}
			pointXA.y += ystep;
			pointXA.x += xstep;
	}

	return (pointXA);
}

t_coor	verticalCast(t_coor point, t_coor origine, double angle)
{
	t_coor pointYA = firstIntersectionVertical(point, origine, angle);

	double ystep = (double)GRID * tan(angle);
	double xstep = GRID;

	//facing left
	if (point.x < origine.x)
		xstep *= -1;

	// facing up
	if (point.y < origine.y && ystep > 0)
		ystep *= -1;
	// facing down
	if (point.y > origine.y && ystep < 0)
		ystep *= -1;

	while (pointYA.x >= 0 && pointYA.x < LENGTH &&
			pointYA.y >= 0 && pointYA.y < HEIGHT)
	{
		if (map[(int)(pointYA.y / GRID)][(int)(pointYA.x / GRID)] == '1' || 
			(xstep < 0 && map[(int)(pointYA.y / GRID)][(int)((pointYA.x - 1) / GRID)] == '1'))
			break ;
		pointYA.y += ystep;
		pointYA.x += xstep;
	}

	return (pointYA);
}

/*	selon un point (ex ray.b (qui est une rotation de img.a)) et une origine (ex milieu trinagle)
 *	prolonge la droite point origine, jusqu'a atteindre un mur
 *	verifie la detection de mur avec xa et ya (detection horizontal et vertical)
 *	renvoie les coor juste avant le mur
*/

double 	ray(t_frame *img, t_coor point, t_coor origine, int color, double angle, int *poslwall)
{
	(void)img;
	(void)color;

	t_coor pointXA = horizontalCast(point, origine, angle);
	t_coor pointYA = verticalCast(point, origine, angle);

	double lxa = getLengthRay(pointXA, origine, angle);
	double lya = getLengthRay(pointYA, origine, angle);

	if (round(lxa) < round(lya))
	{
		put_pixel(img, pointXA.y, pointXA.x, color);
		*poslwall = (int)pointXA.x % GRID;
		return (lxa);
	}
	else 
	{
		put_pixel(img, pointYA.y, pointYA.x, color);
		*poslwall = (int)pointYA.y % GRID;
		return (lya);
	}
	return (-1);
}

//	display une bande de pixel correspondant a un rayon
//	bande qui comment ce la posx et fait h de haut et l de large

void	displayRay(t_frame *img, int posx, int posy, int h, int l, int color, t_img *wall, int posxwall, 
		double ratio_imgwall_strip_h, int posy_strip_imgwall)
{
	int	i = 0;
	int j = 0;

	(void)posy_strip_imgwall;
	(void)ratio_imgwall_strip_h;
	(void)posxwall;

	// - posxwall est la hauteur ou on check la couleur du pixel (quasi tout le temps 0 sauf quand le mur > ecran de proj)
	// - ratio_imgwall_strip_h est le ratio (wall->width / h), a multiplier par le i pour fit la texture dans h
	// - posy_strip_imgwall est la colonne dans la texture 

	int wallpixel;

	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			wallpixel = *(int *)(wall->addr + posxwall * wall->length + 
						(int)(i * ratio_imgwall_strip_h) * wall->length + 
						posy_strip_imgwall * (wall->bpp / 8) + 
						j * (wall->width / 8));

			if (color && posy_strip_imgwall != 0)
				put_pixel(img, posx + i, posy + j, wallpixel);
			else if (color && posy_strip_imgwall == 0)
				put_pixel(img, posx + i, posy + j, 0x00505050);
			else
				put_pixel(img, posx + i, posy + j, color);
			j++;
		}
		i++;
	}
	/* ft_putnbr_fd(incxwall * h, 1);
	ft_putstr_fd(" ", 1); */
}

void	displayRays(t_frame *img, double length, double nbrays, int color, int i, t_img *wall, int poslwall)
{
	// hauteur longeur d'img2
	const double himg = HEIGHT2;
	const double limg = LENGTH2;

	// distance entre la camera et l'ecran de projection (check doc)
	double distce = (himg / 2) / tan(deg2rad(30));

	// largeur des bandes a display dans img2
	double l = limg / nbrays;

	// affichage droite a gauche 
	int posy = limg - 1;

	// hauteur d'un mur selon la projection de l'ecran check (doc)
	double h = ((double)GRID / length) * distce;

	//position x (nb ligne) dans img2
	int posx = (himg / 2) - (h / 2);


///////////////////////////////////////////////////////////////////////////////////

	// ratio a multiplie (par la hauteur) pour fit wall->height dans la bande de hauteur h
	double ratio_imgwall_projectplane_h = (double)wall->height / h;

	// position de x/y dans l'image de la texture
	int posxwall = 0;
	// poslwall et le modulo (% GRID) ou le rayon a ete touche, il est multiplier par le ratio
	// de la largeur de la texture (ex une largeur texture != GRID)
	int posywall = poslwall * wall->width / GRID;


	// possible que le mur (h) soit hors ecran (ex: lorsqu'on est colle au mur) checker si d'autres cas ou segfault
	if (posx < 0)
		posx = 0;

	if (h > himg)
	{
		// si h et sup a l'ecran de projection alors il faut changer de position 
		// dans l'image de texture et commencer a posxwall et non plus 0
		posxwall = ((int)h - himg) / 2 * ratio_imgwall_projectplane_h;
		h = himg - 1;
	}

///////////////////////////////////////////////////////////////////////////////

	(void)ratio_imgwall_projectplane_h;

	/* ft_putnbr_fd(posxwall, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(h, 1);
	ft_putstr_fd("\n", 1); */
	/* ft_putnbr_fd(ratio_imgwall_projectplane_h, 1);
	ft_putstr_fd("\n", 1); */

	//display les brande des pixel h x l, a la pos x/y
	displayRay(img, posx, posy - l * i, h, l, color, wall, posxwall, ratio_imgwall_projectplane_h, posywall);

}

void	castRays(t_data *data, t_frame *img, t_frame *img2, t_coor origine, double nbrays, int color, int color2)
{
    t_coor      rayn;
	int			i;

	(void) img2;
	(void)nbrays;
	(void)origine;
	(void)color2;
	(void)data;

	i = 0;

	double current_angle = 60;

    double      angleinc = deg2rad(current_angle / (double)(LENGTH)); 

	// angle place a haut droit du triangle (60deg depuis (x,y)(1,0)) comment dans un repere classique
	double angle = getAnlge(img->ray.c, origine);

	// pos de depart des rays 
	rayn.x = img->ray.c.x;
	rayn.y = img->ray.c.y;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// la bande ou le rayon a ete touche sur le mur rayon % GRID(check ray())
	int poslwall;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (i < nbrays)
	{
		rotatePoint(angleinc, &rayn.x, &rayn.y, img->triangle.milieu);
		angle += angleinc;
	
		double length = ray(img, rayn, origine, color, angle, &poslwall);

		//fishe eye
		double res = getAnlge(img->triangle.a, origine) - getAnlge(rayn, origine);

		if (res < 0)
			res += deg2rad(360);

		length *= cos(res);

		/* ft_putnbr_fd(poslwall, 1);
		ft_putstr_fd("\n", 1); */

		displayRays(img2, length, nbrays, color2, i, &data->wall, poslwall);

		i++;
	}
}



