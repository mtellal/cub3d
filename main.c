/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:31:58 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/17 22:18:47 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

//	ARROWS	//

#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361




typedef struct s_frame
{
	void	*img;
	char	*addr;
	int	bpp;
	int	length;
	int	endian;
}		t_frame;

void    put_pixel(t_frame *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->length) + x * (img->bpp / 8)) = color;
}

void	draw_triangle(t_frame *img, int l, int x, int y, int color)
{
	int	i = 0;
	int	j = 0;

	while (i <= l)
	{
		j = 0;
		while (j <= i * 2)
		{	
			put_pixel(img, x - i + j, y + i, color);
			j++;
		}
		i++;
	}
}

int	moove(int keycode, t_frame *img)
{
	(void)img;
	//char *buffer = ft_itoa(keycode);
	//write(1, buffer, 20);
	if (UP == keycode)
		write(1, "UP", 2);
	else if (DOWN == keycode)
		write(1, "DOWN", 4);
	else if (RIGHT == keycode)
		write(1, "RIGHT", 5);
	else if (LEFT == keycode)
		write(1, "LEFT", 4);
	return (0);
}

int main()
{
	t_frame	img;

	void *mlx = mlx_init();
	void *mlx_window = mlx_new_window(mlx, 200, 200, "cub3d");
	
	mlx_key_hook(mlx_window, moove, &img);


	img.img = mlx_new_image(mlx, 200, 200);
	
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);
	
	draw_triangle(&img, 10, 50, 50, 0xFFFFFF);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	
	
	mlx_loop(mlx);
	
}
