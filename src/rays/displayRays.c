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

	// plafond
	int pi = 0;
	while (pi < posx)
	{
		put_pixel(img, pi, posy, WALLCOLOR);
		pi++;
	}

	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			wallpixel = *(int *)(wall->addr + posxwall * wall->length + 
						(int)(i * ratio_imgwall_strip_h) * wall->length + 
						posy_strip_imgwall * (wall->bpp / 8) + 
						j * (wall->bpp / 8));

			if (color && posy_strip_imgwall != 0)
				put_pixel(img, posx + i, posy - j, wallpixel);
			else if (color && posy_strip_imgwall == 0)
				put_pixel(img, posx + i, posy - j, 0x00505050);
			else
				put_pixel(img, posx + i, posy - j, color);
			j++;
		}
		i++;
	}

	/* int si = posx + h;
	while (si < HEIGHT2)
	{
		put_pixel(img, si, posy, 0);
		si++;
	} */

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
	//double scale_x = (double)wall->width / h;
	double scale_y = (double)wall->height / h;

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
		posxwall = ((int)h - himg) / 2 * scale_y;
		h = himg - 1;
	}

	//display les brande des pixel h x l, a la pos x/y
	displayRay(img, posx, posy - (int)l * i, h, l, color, wall, posxwall, scale_y, posywall);

}
