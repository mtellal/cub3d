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


void	miniMap(t_data *data, t_frame *minimap, t_frame *img3D)
{
        int pos_playerx = minimap->triangle.milieu.x;
	int pos_playery = minimap->triangle.milieu.y;
	
	int debut_minimapx = pos_playerx - 5 * GRID;
	int debut_minimapy = pos_playery - 5 * GRID;

         if (pos_playerx + 5 * GRID >= minimap->width)
                debut_minimapx -= pos_playerx + 5 * GRID - minimap->width;
        if (pos_playery + 5 * GRID >= minimap->height)
                debut_minimapy -= pos_playery + 5 * GRID - minimap->height;

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
                        if (debut_minimapy + i < minimap->height && debut_minimapx + j < minimap->width)
                        {
			        pixelMinimap = *(int*)(minimap->addr + 
                                                debut_minimapy * minimap->length + 
                                                i * minimap->length +
                                                debut_minimapx * (minimap->bpp / 8) +
                                                j * (minimap->bpp / 8));
                        }

                        if (i == 0 || j == 0 || i + 1 >= GRID * 10 || j + 1 >= GRID * 10)
                                put_pixel(img3D, (data->height - data->height * 0.1 * 6) * GRID * 2 + i, (data->len - 6) * GRID * 2 + j, 0x00FFFFFF);
			else
                                put_pixel(img3D, (data->height - data->height * 0.1 * 6) * GRID * 2 + i, (data->len - 6) * GRID * 2 + j, pixelMinimap);
			j++;
		}
		i++;
	}
}

void    displayRays2D(t_frame *img2D, t_ray **rays, int color)
{
        t_coor  _ray;
        int     i;

        i = 0;
        while (i < img2D->width)
        {
                if (rays[i])
                {
                        _ray = rays[i]->coor;
                       put_pixel(img2D, _ray.y, _ray.x, color);
                }
                i++;
        }
}

void    cast_and_display(t_data *data)
{
        draw_triangle(&data->img2D, data->img2D.triangle, data->img2D.triangle.color);
        data->rays = castRays(data);
        if (!data->rays)
                ft_putstr_fd("ERROR !RAYS", 1);
        displayRays2D(&data->img2D, data->rays, 0x00FFFFFF);
        displayRays(&data->img3D, data->img2D.width, data->rays, &data->texture);
        //miniMap(data, &data->img2D, &data->img3D);
	mlx_put_image_to_window(data->mlx, data->img3D.window, data->img3D.img, 0, 0);
}

void    erasePrecedentStateMovement(t_data *data)
{
        if (data->rays)
        {
                draw_triangle(&data->img2D, data->img2D.triangle, 0);
                displayRays2D(&data->img2D, data->rays, 0);
                free_rays(data->rays, data->img2D.width);
                data->rays = NULL;
        }
}

void    move(t_data *data)
{
	t_frame *img2D = &data->img2D;
        t_coor  direction_incup;
        t_coor  direction_incrigth;

        (void)img2D;
        (void)direction_incup;
        (void)direction_incrigth;

        if (!img2D->move)
    	        return ;
        
        erasePrecedentStateMovement(data);

        // coor a incrementer pour continuer la droite vers le haut/bas - droite/gauche
        direction_incup = coorLine(img2D->triangle.a, img2D->triangle.milieu);
        direction_incrigth = coorLine(img2D->triangle.c, img2D->triangle.b);

        if (img2D->move & U)
                moveUP(data, img2D, direction_incup);
        if (img2D->move & D)
                moveDOWN(data, img2D, direction_incup);
        if (img2D->move & R) 
                moveRIGHT(data, img2D, direction_incrigth);
        if (img2D->move & L)
                moveLEFT(data, img2D, direction_incrigth);
        if (img2D->move & VR)
                moveVRIGHT(img2D);
        if (img2D->move & VL)
                moveVLEFT(img2D);

        cast_and_display(data);
} 

