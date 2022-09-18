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
 	/* t_coor	point;
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
	} */

	put_pixel(img, triangle.a.x, triangle.a.y ,triangle.color);
/* 	put_pixel(img, triangle.b.x, triangle.b.y ,triangle.color);
	put_pixel(img, triangle.c.x, triangle.c.y ,triangle.color); */
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
	 if (UP == keycode)
	{
		write(1, "UP ", 3);
		new_frame(img);
		if (img->triangle.a.y - 5 > 0)
		{
			img->triangle.a.y -= 5;
			img->triangle.b.y -= 5;
			img->triangle.c.y -= 5;
		}
		draw_triangle(img, img->triangle);
		push_frame(img);
	}
	else if (DOWN == keycode)
	{
		write(1, "DOWN ", 5);
		new_frame(img);
		if (img->triangle.b.y + 5 < 200 || img->triangle.c.y + 5 < 200 )
		{
			img->triangle.a.y += 5;
			img->triangle.b.y += 5;
			img->triangle.c.y += 5;
		}
		draw_triangle(img, img->triangle);
		push_frame(img);
	}
	else if (RIGHT == keycode)
	{
		write(1, "RIGHT ", 6);
		new_frame(img);
		img->triangle.a.x += 5;
		img->triangle.b.x += 5;
		img->triangle.c.x += 5;
		draw_triangle(img, img->triangle);
		push_frame(img);
	}
	else if (LEFT == keycode)
	{
		write(1, "LEFT ", 5);
		new_frame(img);
		img->triangle.a.x -= 5;
		img->triangle.b.x -= 5;
		img->triangle.c.x -= 5;
		draw_triangle(img, img->triangle);
		push_frame(img);
	}
	else if (VRIGHT == keycode)
	{
		int		angle = 90;

		write(1, "CAM_RIGTH \n", 11);
		new_frame(img);

		draw_triangle(img, img->triangle);

		int	apos_x = img->triangle.milieu.x - img->triangle.a.x;
		int	apos_y = img->triangle.milieu.y - img->triangle.a.y;

		img->triangle.a.x = (apos_x * cos(angle)) + (apos_y * -sin(angle));
		img->triangle.a.x += img->triangle.milieu.x;

		img->triangle.a.y = (apos_x * sin(angle)) + (apos_y* cos(angle));
		ft_putnbr_fd(img->triangle.a.y, 1);
		img->triangle.a.y += img->triangle.milieu.y;

		ft_putnbr_fd(img->triangle.a.y, 1);

/* 
		img->triangle.b.x = (img->triangle.b.x - img->triangle.milieu.x) * cos(angle) - 
			(img->triangle.b.y - img->triangle.milieu.y)  * sin(angle) + img->triangle.milieu.x;

		img->triangle.b.y = (img->triangle.b.x - img->triangle.milieu.x) * sin(angle) + 
		(img->triangle.b.y - img->triangle.milieu.y)  * cos(angle) + img->triangle.milieu.y;


		img->triangle.c.x = (img->triangle.c.x - img->triangle.milieu.x) * cos(angle) - 
			(img->triangle.c.y - img->triangle.milieu.y)  * sin(angle) + img->triangle.milieu.x;

		img->triangle.c.y = (img->triangle.c.x - img->triangle.milieu.x) * sin(angle) + 
		(img->triangle.c.y - img->triangle.milieu.y)  * cos(angle) + img->triangle.milieu.y;
 */

		//draw_triangle(img, img->triangle);
		/* put_pixel(img, img->triangle.a.x, img->triangle.a.y, 0xFABC);
		put_pixel(img, img->triangle.b.x, img->triangle.c.y, 0xFABC);
		put_pixel(img, img->triangle.c.x, img->triangle.c.y, 0xFABC); */

		draw_triangle(img, img->triangle);
		push_frame(img);

	}
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

	img.triangle.b.x = 40;
	img.triangle.b.y = 70;

	img.triangle.c.x = 70;
	img.triangle.c.y = 70;

	img.triangle.milieu.x = 55;
	img.triangle.milieu.y = 65;

	img.triangle.color = 0xFFFFFF;

	put_pixel(&img, img.triangle.milieu.x, img.triangle.milieu.y, 0x00FF0000);

	draw_triangle(&img, img.triangle);
	mlx_put_image_to_window(img.mlx, img.window, img.img, 0, 0);
	
	
	mlx_loop(img.mlx);
	
}
