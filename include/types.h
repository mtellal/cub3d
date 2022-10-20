/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:25:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/20 12:33:35 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H


enum s_directions
{
	NORD,
	SUD,
	OUEST,
	EST
};

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
	
	int	*color;
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

typedef struct s_ray
{
	double length;
	t_coor coor;
	int posstripwall;
	int walldirection;

}				t_ray;

typedef struct s_frame
{
	void				*window;
	void				*img;
	char				*addr;

	int					bpp;
	int					length;
	int					endian;

	struct s_triangle	triangle;
	int					move;

	int					height;
	int					width;

}		t_frame;

typedef struct s_texture
{
	t_img	walln;
	t_img	walls;
	t_img	wallo;
	t_img	walle;

	int		cieling;
	int		floor;

}				t_texture;

typedef struct s_data
{
	void	*mlx;

	t_frame img2D;
	t_frame img3D;
	t_texture texture;
	t_ray **rays;


	char	**map;
	int		len;
	int		height;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*f_texture;
	char	*c_texture;

}				t_data;

#endif
