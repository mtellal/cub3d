/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:28:34 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/19 16:29:14 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <math.h>

#include "macros.h"
#include "types.h"


extern char	map[MHEIGHT][MLENGTH];

// main.c

// init.c
void	initTriangle(t_frame *img, int i, int j);
void	fillWalls(t_frame *img, char map[MHEIGHT][MLENGTH]);
void	init(t_data *img);


// utils.c
t_coor	coorLine(t_coor point, t_coor origine);
double	getAnlge(t_coor point, t_coor origine);
void	displayCoor(t_coor point);
double	abs_value(double value);
double	getLengthRay(t_coor point, t_coor origine, double angle);
int     checkWall(char map[MHEIGHT][MLENGTH], int x, int y);
void    free_rays(t_ray **rays, int l);


/////////////////           DRAW            ///////////////////

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle, int color);
void	draw_wall(t_frame *, t_wall, int, int);
float barycentre (t_coor p1, t_coor p2, t_coor p3);
int dansLeTriangle (t_coor pt, t_triangle t);



////////////////            RAYS            /////////////////

// rays.c
t_ray	**castRays(t_frame *img);

// horizontal_cast.c
t_coor	firstIntersectionHorizontal(t_coor point, t_coor origine, double angle);
t_coor	horizontalCast(t_coor point, t_coor origine, double angle);


// vertical_cast.c
t_coor	firstIntersectionVertical(t_coor point, t_coor origine, double angle);
t_coor	verticalCast(t_coor point, t_coor origine, double angle);

/////////////// DISPLAY

// displayRays.c
void	displayCastRays(t_frame *img, t_ray **rays, t_texture *texture);

// utils.c
double	correctFishEye(double length, double cumulangle);
t_ray	**initTabRays(void);


////////////////            MOVE            /////////////////

// move.c
void	miniMap(t_frame *minimap, t_frame *img);
void    move(t_data *img);

// movements.c
void    moveUP(t_frame *img, t_coor dda_inc);
void    moveDOWN(t_frame *img, t_coor dda_inc);
void    moveRIGHT(t_frame *img, t_coor dda_inc);
void    moveLEFT(t_frame *img, t_coor dda_inc);

//  vmovements.c
double  deg2rad(double degrees);
double  rad2deg(double radians);
void    moveVRIGHT(t_frame *img);
void    moveVLEFT(t_frame *img);


//  rotate.c
double      rotateX(double angle, double x, double y, int r);
double      rotateY(double angle, double x, double y, int r);
void        rotatePoint(double angle, double *x, double *y, t_coor origine);
void        rrotatePoint(double angle, double *x, double *y, t_coor origine);





///////////////         EVENTS             ////////////////

//events.c
int	handle_input(void *img);
int keyPressed(int keycode, t_frame *img);
int keyReleased(int keycode, t_frame *img);


#endif
