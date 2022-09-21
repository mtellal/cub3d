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

#include "cub3d.h"

char map[HEIGHT][LENGTH] = 
{
{'0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
{'0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'0','0','0','0','0','0','0','0','1','0','1','1','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'1','1','1','1','1','1','1','1','1','0','1','1','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1'},
{'1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'},
{'1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1','0','1','0','0','1','0','0','0','1','0','0','0','0'},
{'1','1','0','0','0','0','0','0','1','1','0','1','0','1','0','1','1','1','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'},
{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'},
{'1','0','0','0','0','0','0','N','0','0','0','0','0','0','0','0','1','1','0','1','0','1','0','0','1','0','0','0','1','0','0','0','0'},
{'1','1','0','0','0','0','0','1','1','1','0','1','0','1','0','1','1','1','1','1','0','1','1','1','1','0','0','0','1','1','1','0','0'},
{'1','1','1','1','0','1','1','1','0','1','1','1','0','1','0','1','0','1','0','1','1','1','1','0','1','0','0','0','1','0','0','0','0'},
{'1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','0'}
};

// ligne 9
// lligne 33

void	fillWalls(t_frame *img, char map[14][35])
{
	int i = 0;
	int j = 0;
	t_wall	w;
/* 	t_wall	perso; */

	w.size = GRID;
	w.color = 0x00B0FF00;
/* 	perso.size = 20;
	perso.color = 0x00250060; */

	while (i < 14)
	{
		j = 0;
		while (j < 35)
		{
			if (map[i][j] == '1')
				draw_wall(img, w, i * w.size, j * w.size);
			else if (map[i][j] == 'N')
			{
				img->triangle.ipos.x = i * w.size;
				img->triangle.ipos.y = j * w.size;

				img->triangle.a.x = j * GRID + GRID / 2;
				img->triangle.a.y = i * GRID + GRID / 4;

				img->triangle.b.x = j * GRID + GRID / 4;
				img->triangle.b.y = i * GRID + GRID * 0.75;

				img->triangle.c.x = j * GRID + GRID * 0.75;
				img->triangle.c.y = i * GRID + GRID * 0.75;

				img->triangle.milieu.x = j * GRID + GRID / 2;
				img->triangle.milieu.y = i * GRID + GRID / 2;

				img->triangle.color = 0x00F50600;

				put_pixel(img, img->triangle.milieu.y, img->triangle.milieu.x, 0x00FF5689);
				//draw_wall(img, w, i * w.size, j * w.size);

				draw_triangle(img, img->triangle);
 			}
			j++;
		}
		i++;
	}
}

int keyReleased(int keycode, t_frame *img)
{
	if (keycode == UP)
	{
		img->move &= ~U;
	}
	if (keycode == DOWN)
	{
		img->move &= ~D;
	}
	if (keycode == RIGHT)
	{
		img->move &= ~R;
	}
	if (keycode == LEFT)
	{
		img->move &= ~L;
	}
	if (keycode == VRIGHT)
	{
		img->move &= ~VR;
	}
	if (keycode == VLEFT)
	{
		img->move &= ~VL;
	}
	return (0);
}

int	handle_input(void *img)
{
	move(img);
	return (0);
}

int keyPressed(int keycode, t_frame *img)
{
	(void)img;
	if (keycode == UP)
	{
		img->move |= U;
	}
	if (keycode == DOWN)
	{
		img->move |= D;
	}
	if (keycode == RIGHT)
	{
		img->move |= R;
	}
	if (keycode == LEFT)
	{
		img->move |= L;
	}
	if (keycode == VRIGHT)
	{
		img->move |= VR;
	}
	if (keycode == VLEFT)
	{
		img->move |= VL;
	}

	return (0);
}

int main()
{
	t_frame	img;

	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, LENGTH * GRID, HEIGHT * GRID, "cub3d");
	
	img.img = mlx_new_image(img.mlx, LENGTH * GRID, HEIGHT * GRID);
	
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);

	//img.move = 0;

	fillWalls(&img, map);

 	mlx_hook(img.window, 3, 1L<<1, keyReleased, &img);

	mlx_hook(img.window, 2, 1L<<0,  keyPressed, &img);
 
	mlx_loop_hook(img.mlx, handle_input, &img);
	mlx_loop(img.mlx);
}
