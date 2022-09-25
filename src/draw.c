/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:08:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/19 16:08:43 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_pixel(t_frame *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (x * img->length) + y * (img->bpp / 8)) = color;
}

void	new_frame(t_frame *img)
{
	img->img = mlx_new_image(img->mlx, LENGTH * GRID , HEIGHT * GRID);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, &img->endian);

}

void	push_frame(t_frame *img)
{
	mlx_put_image_to_window(img->mlx, img->window, img->img, 0, 0);
}

void	draw_triangle(t_frame *img, t_triangle triangle, int color)
{
 	t_coor	point;
	int	i = triangle.ipos.l;
	int	j = triangle.ipos.h;

	while (i < triangle.ipos.l + GRID)
	{
		j = 0;
		while (j < triangle.ipos.h + GRID)
		{
			point.x = i;
			point.y = j;
			if (dansLeTriangle(point, triangle))
				put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}

	/* put_pixel(img, triangle.a.y, triangle.a.x ,0x0000FF00);
	put_pixel(img, triangle.b.y, triangle.b.x ,0x00FF00FF);
	put_pixel(img, triangle.c.y, triangle.c.x ,0x00F0F000);
	put_pixel(img, triangle.milieu.y, triangle.milieu.x, 0x00FFFFFF); */

}

/*	display un mur au sein d'une cellule
 *	le mur affiche est plus petit que la cellule d'ou le 0.1/0.9
*/
void	draw_wall(t_frame *img, t_wall w, int x, int y)
{
	size_t	i = x;
	size_t	j = y;

	while (i < w.size + x)
	{
		j = y;
		while (j < w.size + y)
		{
			if (i > w.size * 0.1 + x && i < w.size * 0.9 + x &&
				j > w.size * 0.1 + y && j < w.size * 0.9 + y)
			put_pixel(img, i, j, w.color);
			j++;
		}
		i++;
	}
}