/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:09:21 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/19 16:10:16 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
#define DRAW_H

#include "types.h"

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle);
void	draw_wall(t_frame *, t_wall, int, int);

void	new_frame(t_frame *img);
void	push_frame(t_frame *img);

int	moove(int keycode, t_frame *img);
void	fillWalls(t_frame *img, char map[14][35]);



#endif
