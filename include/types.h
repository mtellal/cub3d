/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:25:49 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 15:12:00 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

enum	e_directions
{
	NORD,
	SUD,
	OUEST,
	EST
};

typedef struct s_coor
{
	double	x;
	double	y;
}			t_coor;

typedef struct s_coor_map
{
	double	h;
	double	l;
}				t_coor_map;		

typedef struct s_img
{
	int		length;
	int		bpp;
	int		endian;
	int		height;
	int		width;
	int		*color;
	void	*img;
	char	*addr;
}				t_img;

typedef struct s_triangle
{
	int			color;
	t_coor		a;
	t_coor		b;
	t_coor		c;
	t_coor		milieu;
	t_coor		no;
	t_coor		ne;
	t_coor		so;
	t_coor		se;
	t_coor_map	ipos;
}				t_triangle;

typedef struct s_drays
{
	t_coor		piw;
	t_coor		pw;
	t_coor_map	w;
}				t_drays;

typedef struct s_ray
{
	int			posstripwall;
	int			walldirection;
	double		length;
	t_coor		coor;

}				t_ray;

typedef struct s_frame
{
	int				bpp;
	int				length;
	int				endian;
	int				move;
	int				height;
	int				width;
	void			*window;
	void			*img;
	char			*addr;
	t_triangle		triangle;

}		t_frame;

typedef struct s_texture
{
	int		cieling;
	int		floor;
	t_img	walln;
	t_img	walls;
	t_img	wallo;
	t_img	walle;
}				t_texture;

typedef struct s_data
{
	int			len;
	int			height;
	void		*mlx;
	char		**map;
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		*f_texture;
	char		*c_texture;
	t_frame		img2d;
	t_frame		img3d;
	t_texture	texture;
	t_ray		**rays;
}				t_data;

#endif
