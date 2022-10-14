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

/*	verifie si le masque est non nul, alors une touche est presse
 *	efface le triangle
 *	call les functions moveX correspondant aux touches pressees, peut etre en meme temps
 *	display le triangle et push l'image dans la fenetre
 */

void    move(t_data *data)
{
	t_frame *img = &data->img;
        
        if (!img->move)
    	        return ;
        
        // coor a incrementer pour continuer la droite vers le haut/bas - droite/gauche
        t_coor dda_incup = coorLine(img->triangle.a, img->triangle.milieu);
        t_coor dda_incrigth = coorLine(img->triangle.c, img->triangle.b);

       /*  put_pixel(&data->img, img->triangle.no.y, img->triangle.no.x, 0);
        put_pixel(&data->img, img->triangle.ne.y, img->triangle.ne.x, 0);
        put_pixel(&data->img, img->triangle.so.y, img->triangle.so.x, 0);
        put_pixel(&data->img, img->triangle.se.y, img->triangle.se.x, 0); */


        castRays(data, &data->img, &data->img2, img->triangle.milieu, LENGTH, 0, 0);
        draw_triangle(img, img->triangle, 0);

        if (img->move & U)
                moveUP(img, dda_incup);
        if (img->move & D)
                moveDOWN(img, dda_incup);
        if (img->move & R) 
                moveRIGHT(img, dda_incrigth);
        if (img->move & L)
                moveLEFT(img, dda_incrigth);
        if (img->move & VR)
                moveVRIGHT(img);
        if (img->move & VL)
                moveVLEFT(img);

	castRays(data, &data->img, &data->img2, img->triangle.milieu, LENGTH, 0x00FFFFFF, 1);
	draw_triangle(img, img->triangle, img->triangle.color);

    /*     put_pixel(&data->img, img->triangle.no.y, img->triangle.no.x, 0x00FFFFFF);
        put_pixel(&data->img, img->triangle.ne.y, img->triangle.ne.x, 0x00FFFFFF);
        put_pixel(&data->img, img->triangle.so.y, img->triangle.so.x, 0x00FFFFFF);
        put_pixel(&data->img, img->triangle.se.y, img->triangle.se.x, 0x00FFFFFF); */

        miniMap(&data->img, &data->img2);

        //push_frame(img);
        push_frame(&data->img2);
} 

