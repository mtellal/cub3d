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

//  rays.c
void	draw_square(t_frame *img, int h, int l, t_coor_map pos, int color);
void	edgeSquare(t_frame *img, int h, int l, t_coor_map pos, int color);
void	castRays(t_data *data, t_frame *img, t_frame *img2, t_coor origine, double nbrays, int color, int color2);

// utils.c
t_coor	coorLine(t_coor point, t_coor origine);
double	getAnlge(t_coor point, t_coor origine);
void	displayCoor(t_coor point);
double	abs_value(double value);
double	getLengthRay(t_coor point, t_coor origine, double angle);
int     checkWall(char map[MHEIGHT][MLENGTH], int x, int y);


/////////////////           DRAW            ///////////////////

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle, int color);
void	draw_wall(t_frame *, t_wall, int, int);
float barycentre (t_coor p1, t_coor p2, t_coor p3);
int dansLeTriangle (t_coor pt, t_triangle t);



////////////////            RAYS            /////////////////

// displayRays.c
void	displayRay(t_frame *img, int posx, int posy, int h, int l, int color, t_img *wall, int posxwall, 
		double ratio_imgwall_strip_h, int posy_strip_imgwall);
void	displayRays(t_frame *img, double length, double nbrays, int color, int i, t_img *wall, int poslwall);

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
