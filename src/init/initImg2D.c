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

int		ft_belong(char c, char *s)
{
	int 	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

/* affiche les murs et init le triangle lorsque N est trouve
 * note: les murs sont affiches qu'une seul fois, les events modifient uniquement le triangle 
*/

void	fillImg2D(t_data *data, t_frame *img2D)
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
			else if (ft_belong(data->map[i][j], "NSEW"))
			{
				initTriangle(img2D, i, j, data->map[i][j]);
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
    fillImg2D(data, img2D);
}