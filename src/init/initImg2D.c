/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initImg2D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:09:12 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/19 16:09:19 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
	img2D->img = mlx_new_image(data->mlx, img2D->width, img2D->height);
	img2D->addr = mlx_get_data_addr(img2D->img, &img2D->bpp, &img2D->length, &img2D->endian);
	img2D->move = 0;
    fillWalls(data, img2D);
}