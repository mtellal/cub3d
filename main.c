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
#include <math.h>

//	ARROWS	//

/* #define UP 65362
#define DOWN 65364 */
#define VRIGHT 65363
#define VLEFT 65361

#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

typedef struct s_coor
{
	double x;
	double y;
}			t_coor;

typedef struct s_triangle
{
	struct s_coor ipos;
	
	struct s_coor a;
	struct s_coor b;
	struct s_coor c;

	struct s_coor milieu;

	int color;
}				t_triangle;

typedef struct s_frame
{
	void				*mlx;
	void				*window;
	void				*img;
	char				*addr;
	int					bpp;
	int					length;
	int					endian;
	struct s_triangle	triangle;
}		t_frame;


float barycentre (t_coor p1, t_coor p2, t_coor p3)
{
    return (float)((p1.x - p3.x) * (p2.y - p3.y)) - (float)((p2.x - p3.x) * (p1.y - p3.y));
}
 
int dansLeTriangle (t_coor pt, t_triangle t)
{
    int b1, b2, b3;
 
	b1 = 0;
	b2 = 0;
	b3 = 0;
    if (barycentre(pt, t.a, t.b) < 0)
		b1 = 1;
	if (barycentre(pt, t.b, t.c) < 0)
		b2 = 1;
	if (barycentre(pt, t.c, t.a) < 0)
		b3 = 1;
 
    return ((b1 == b2) && (b2 == b3));
}

void    put_pixel(t_frame *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->length) + x * (img->bpp / 8)) = color;
}

void	draw_triangle(t_frame *img, t_triangle triangle)
{
 	t_coor	point;
	int	i = 0;
	int	j = 0;
	
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			point.x = i;
			point.y = j;
			if (dansLeTriangle(point, triangle))
				put_pixel(img, i, j, triangle.color);
			j++;
		}
		i++;
	}

	put_pixel(img, triangle.a.x, triangle.a.y ,0x0000FF00);
	put_pixel(img, triangle.b.x, triangle.b.y ,0x00FF00FF);
	put_pixel(img, triangle.c.x, triangle.c.y ,0x00F0F000);
	put_pixel(img, triangle.milieu.x, triangle.milieu.y, 0x00FF0000);

}


 void	new_frame(t_frame *img)
{
	img->img = mlx_new_image(img->mlx, 200, 200);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, &img->endian);

}

void	push_frame(t_frame *img)
{
	mlx_put_image_to_window(img->mlx, img->window, img->img, 0, 0);
}

int	moove(int keycode, t_frame *img)
{
	(void)img;
	//char *buffer = ft_itoa(keycode);
	//write(1, buffer, 20);
	new_frame(img);
	 if (UP == keycode)
	{
		write(1, "UP ", 3);
		if (img->triangle.a.y - 5 > 0 && img->triangle.b.y - 5 > 0 && 
			img->triangle.c.y - 5 > 0)
		{
			img->triangle.a.y -= 5;
			img->triangle.b.y -= 5;
			img->triangle.c.y -= 5;
			img->triangle.milieu.y -= 5;
		}
	}
	else if (DOWN == keycode)
	{
		write(1, "DOWN ", 5);
		if (img->triangle.milieu.y + 5 < 200)
		{
			img->triangle.a.y += 5;
			img->triangle.b.y += 5;
			img->triangle.c.y += 5;
			img->triangle.milieu.y += 5;
		}
	}
	else if (RIGHT == keycode)
	{
		write(1, "RIGHT ", 6);
		if (img->triangle.c.x < 200)
		{
			img->triangle.a.x += 5;
			img->triangle.b.x += 5;
			img->triangle.c.x += 5;
			img->triangle.milieu.x += 5;
		}
	}
	else if (LEFT == keycode)
	{
		write(1, "LEFT ", 5);
		if (img->triangle.b.x >= 0)
		{
			img->triangle.a.x -= 5;
			img->triangle.b.x -= 5;
			img->triangle.c.x -= 5;
			img->triangle.milieu.x -= 5;
		}
	}
	else if (VRIGHT == keycode)
	{
		double		angle = 10;

		write(1, "CAM_RIGTH \n", 11);

		//draw_triangle(img, img->triangle);

		double	apos_x = img->triangle.milieu.x - img->triangle.a.x;
		double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

		img->triangle.a.x = (apos_x * cos(angle)) + (apos_y * -sin(angle));
		img->triangle.a.x += img->triangle.milieu.x;

		img->triangle.a.y = (apos_x * sin(angle)) + (apos_y* cos(angle));
		img->triangle.a.y += img->triangle.milieu.y;


		double	bpos_x = img->triangle.milieu.x - img->triangle.b.x;
		double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

		img->triangle.b.x = (bpos_x * cos(angle)) + (bpos_y * -sin(angle));
		img->triangle.b.x += img->triangle.milieu.x;

		img->triangle.b.y = (bpos_x * sin(angle)) + (bpos_y * cos(angle));
		img->triangle.b.y += img->triangle.milieu.y;


		double	cpos_x = img->triangle.milieu.x - img->triangle.c.x;
		double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

		img->triangle.c.x = (cpos_x * cos(angle)) + (cpos_y * -sin(angle));
		img->triangle.c.x += img->triangle.milieu.x;

		img->triangle.c.y = (cpos_x * sin(angle)) + (cpos_y* cos(angle));
		img->triangle.c.y += img->triangle.milieu.y;

	}
	else if (VLEFT == keycode)
	{
		double		angle = 100;

		write(1, "CAM_LEFT \n", 11);

		//draw_triangle(img, img->triangle);

		double	apos_x = img->triangle.milieu.x - img->triangle.a.x;
		double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

		img->triangle.a.x = (apos_x * -cos(angle)) + (apos_y * sin(angle));
		img->triangle.a.x += img->triangle.milieu.x;

		img->triangle.a.y = (apos_x * -sin(angle)) + (apos_y* -cos(angle));
		img->triangle.a.y += img->triangle.milieu.y;


		double	bpos_x = img->triangle.milieu.x - img->triangle.b.x;
		double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

		img->triangle.b.x = (bpos_x * -cos(angle)) + (bpos_y * sin(angle));
		img->triangle.b.x += img->triangle.milieu.x;

		img->triangle.b.y = (bpos_x * -sin(angle)) + (bpos_y * -cos(angle));
		img->triangle.b.y += img->triangle.milieu.y;


		double	cpos_x = img->triangle.milieu.x - img->triangle.c.x;
		double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

		img->triangle.c.x = (cpos_x * -cos(angle)) + (cpos_y * sin(angle));
		img->triangle.c.x += img->triangle.milieu.x;

		img->triangle.c.y = (cpos_x * -sin(angle)) + (cpos_y* -cos(angle));
		img->triangle.c.y += img->triangle.milieu.y;

	}

	draw_triangle(img, img->triangle);
	push_frame(img);
	return (0); 
} 


int main()
{
	t_frame	img;

	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, 200, 200, "cub3d");
	
	mlx_hook(img.window, 2, 1L<<0,  moove, &img);


	img.img = mlx_new_image(img.mlx, 200, 200);
	
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);
	
	img.triangle.a.x = 50;
	img.triangle.a.y = 50;

	img.triangle.b.x = 20;
	img.triangle.b.y = 80;

	img.triangle.c.x = 80;
	img.triangle.c.y = 80;

	img.triangle.milieu.x = 50;
	img.triangle.milieu.y = 70;

	img.triangle.color = 0x00FFFFFF;

	put_pixel(&img, img.triangle.milieu.x, img.triangle.milieu.y, 0x00FF0000);

	draw_triangle(&img, img.triangle);
	mlx_put_image_to_window(img.mlx, img.window, img.img, 0, 0);
	
	
	mlx_loop(img.mlx);
	
}
