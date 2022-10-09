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

#define HEIGHT 14
#define LENGTH 33
#define GRID 25

/* #define UP 65362
#define DOWN 65364 */
#define VRIGHT 65363
#define VLEFT 65361

#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

//  mask movements
#define U 1
#define D 2
#define R 4
#define L 8
#define VR 16
#define VL 32

#define ANGLE 60

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <math.h>

#include "types.h"


extern char	map[HEIGHT][LENGTH];

// main.c

// init.c
void	initTriangle(t_frame *img, int i, int j);
void	fillWalls(t_frame *img, char map[14][33]);
void	init(t_data *img);

//  rays.c
void	draw_square(t_frame *img, int h, int l, t_coor_map pos, int color);
void	edgeSquare(t_frame *img, int h, int l, t_coor_map pos, int color);
void	castRays(t_frame *img, t_frame *img2, t_coor origine, double nbrays, int color);




/////////////////           OPERATIONS      //////////////////

float barycentre (t_coor p1, t_coor p2, t_coor p3);
int dansLeTriangle (t_coor pt, t_triangle t);




/////////////////           DRAW            ///////////////////

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle, int color);
void	draw_wall(t_frame *, t_wall, int, int);

void	new_frame(t_frame *img);
void	push_frame(t_frame *img);




////////////////            RAYS            /////////////////

//  utils.c
void	draw_line(t_frame *img,  t_coor point, t_coor origine, t_coor *ray_coor, int color, double *lengthline);
t_coor	coorLine(t_coor point, t_coor origine);
double	getAnlge(t_coor point, t_coor origine);
void	displayCoor(t_coor point);
double	abs_value(double value);
double	getLengthRay(t_coor point, t_coor origine, double angle);





////////////////            MOVE            /////////////////

// move.c
void    move(t_data *img);

// movements.c
void    moveUP(t_frame *img);
void    moveDOWN(t_frame *img);
void    moveRIGHT(t_frame *img);
void    moveLEFT(t_frame *img);

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


// utils.c
int     checkWall(char map[HEIGHT][LENGTH], int x, int y);





///////////////         EVENTS             ////////////////

//events.c
int	handle_input(void *img);
int keyPressed(int keycode, t_frame *img);
int keyReleased(int keycode, t_frame *img);


#endif
