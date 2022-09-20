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

typedef struct s_triangle
{
	struct s_coor ipos;

	struct s_coor a;
	struct s_coor b;
	struct s_coor c;

	struct s_coor milieu;

	int color;
}				t_triangle;

typedef struct s_wall
{
    size_t  size;
    int     color;

}               t_wall;

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


#endif
