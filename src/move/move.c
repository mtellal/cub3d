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


void	miniMap(t_frame *minimap, t_frame *img)
{
        (void)img;
        int pos_playerx = minimap->triangle.milieu.x;
	int pos_playery = minimap->triangle.milieu.y;
	
	int debut_minimapx = pos_playerx - 5 * GRID;
	int debut_minimapy = pos_playery - 5 * GRID;

         if (pos_playerx + 5 * GRID >= LENGTH)
                debut_minimapx -= pos_playerx + 5 * GRID - LENGTH;
        if (pos_playery + 5 * GRID >= HEIGHT)
                debut_minimapy -= pos_playery + 5 * GRID - HEIGHT;

	if (debut_minimapx < 0)
		debut_minimapx = 0;
        if (debut_minimapy < 0)
		debut_minimapy = 0;

        
	int i = 0;
	int j = 0;
	while (i < 10 * GRID)
	{
		j = 0;
	        while (j < 10 * GRID)
		{
                        int pixelMinimap = 0;
                        if (debut_minimapy + i < HEIGHT && debut_minimapx + j < LENGTH)
                        {
			        pixelMinimap = *(int*)(minimap->addr + 
                                                debut_minimapy * minimap->length + 
                                                i * minimap->length +
                                                debut_minimapx * (minimap->bpp / 8) +
                                                j * (minimap->bpp / 8));
                        }

                        if (i == 0 || j == 0 || i + 1 >= GRID * 10 || j + 1 >= GRID * 10)
                                put_pixel(img, (MHEIGHT - 6) * GRID * 2 + i, (MLENGTH - 6) * GRID * 2 + j, 0x00FFFFFF);
			else
                                put_pixel(img, (MHEIGHT - 6) * GRID * 2 + i, (MLENGTH - 6) * GRID * 2 + j, pixelMinimap);
			j++;
		}
		i++;
	}
}

void    displayRays2D(t_frame *img, t_ray **rays, int color)
{
        t_coor  _ray;
        int     i;

        i = 0;
        while (i < NBRAYS)
        {
                if (rays[i])
                {
                        _ray = rays[i]->coor;
                       put_pixel(img, _ray.y, _ray.x, color);
                }
                i++;
        }
}

/*	verifie si le masque est non nul, alors une touche est presse
 *	efface le triangle
 *	call les functions moveX correspondant aux touches pressees, peut etre en meme temps
 *	display le triangle et push l'image dans la fenetre
 */

void    move(t_data *data)
{
	t_frame *img2D = &data->img2D;

        if (!img2D->move)
    	        return ;
        
        if (data->rays)
        {
                displayRays2D(&data->img2D, data->rays, 0);
                free_rays(data->rays, NBRAYS);
                data->rays = NULL;
        }

        // coor a incrementer pour continuer la droite vers le haut/bas - droite/gauche
        t_coor dda_incup = coorLine(img2D->triangle.a, img2D->triangle.milieu);
        t_coor dda_incrigth = coorLine(img2D->triangle.c, img2D->triangle.b);

       /*  put_pixel(&data->img, img->triangle.no.y, img->triangle.no.x, 0);
        put_pixel(&data->img, img->triangle.ne.y, img->triangle.ne.x, 0);
        put_pixel(&data->img, img->triangle.so.y, img->triangle.so.x, 0);
        put_pixel(&data->img, img->triangle.se.y, img->triangle.se.x, 0); */


       // castRays(data, &data->img2D, &data->img3D, img2D->triangle.milieu, LENGTH, 0, 0);
        draw_triangle(img2D, img2D->triangle, 0);

        if (img2D->move & U)
                moveUP(img2D, dda_incup);
        if (img2D->move & D)
                moveDOWN(img2D, dda_incup);
        if (img2D->move & R) 
                moveRIGHT(img2D, dda_incrigth);
        if (img2D->move & L)
                moveLEFT(img2D, dda_incrigth);
        if (img2D->move & VR)
                moveVRIGHT(img2D);
        if (img2D->move & VL)
                moveVLEFT(img2D);

        data->rays = castRays(&data->img2D);

        if (data->rays)
        {
                displayRays2D(&data->img2D, data->rays, 0x00FFFFFF);
                displayCastRays(&data->img3D, data->rays, &data->texture);
        }
	//castRays(data, &data->img2D, &data->img3D, img2D->triangle.milieu, LENGTH, 0x00FFFFFF, 1);
	draw_triangle(img2D, img2D->triangle, img2D->triangle.color);


    /*     put_pixel(&data->img, img->triangle.no.y, img->triangle.no.x, 0x00FFFFFF);
        put_pixel(&data->img, img->triangle.ne.y, img->triangle.ne.x, 0x00FFFFFF);
        put_pixel(&data->img, img->triangle.so.y, img->triangle.so.x, 0x00FFFFFF);
        put_pixel(&data->img, img->triangle.se.y, img->triangle.se.x, 0x00FFFFFF); */

        miniMap(&data->img2D, &data->img3D);

	mlx_put_image_to_window(data->mlx, data->img3D.window, data->img3D.img, 0, 0);

       // free_rays(rays, nbrays);
} 

