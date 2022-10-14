/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:25:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/19 16:26:04 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

typedef struct s_coor
{
	double x;
	double y;
}			t_coor;

typedef struct s_coor_map
{
	double h;
	double l;
}				t_coor_map;		

typedef struct s_img
{
	void *img;
	char *addr;
	
	int length;
	int bpp;
	int endian;

	int height;
	int width;
}				t_img;

typedef struct s_triangle
{
	struct s_coor_map ipos;

	struct s_coor a;
	struct s_coor b;
	struct s_coor c;

	struct s_coor milieu;

	struct s_coor no;
	struct s_coor ne;
	struct s_coor so;
	struct s_coor se;

	int color;
}				t_triangle;

typedef struct s_wall
{
    size_t  size;
    int     color;

}               t_wall;

typedef struct s_frame
{
	void				*window;
	void				*img;
	char				*addr;

	int					bpp;
	int					length;
	int					endian;

	struct s_triangle	triangle;
	struct s_triangle	ray;

	int					move;

}		t_frame;

typedef struct s_data
{
	void	*mlx;

	t_frame img2D;
	t_frame img3D;

	t_img wall;
	t_img cieling;
	t_img ground;

}				t_data;

#endif
