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

/* #define UP 65362
#define DOWN 65364 */
#define VRIGHT 65363
#define VLEFT 65361

#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

#define HEIGHT 14
#define LENGTH 35

#define U 1
#define D 2
#define R 4
#define L 8
#define VR 16
#define VL 32

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <math.h>

#include "types.h"


extern char	map[HEIGHT][LENGTH];

/////////////////           OPERATIONS      //////////////////

float barycentre (t_coor p1, t_coor p2, t_coor p3);
int dansLeTriangle (t_coor pt, t_triangle t);

/////////////////           DRAW            ///////////////////

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle);
void	draw_wall(t_frame *, t_wall, int, int);

void	new_frame(t_frame *img);
void	push_frame(t_frame *img);

void    move(t_frame *img);
void	fillWalls(t_frame *img, char map[14][35]);


////////////////            MOVE            /////////////////

// move.c
void    moveVLEFT(t_frame *img);
void    moveVRIGHT(t_frame *img);
void    refillWalls(t_frame *img, char m[14][35]);

// movements.c
void    moveUP(t_frame *img);
void    moveDOWN(t_frame *img);
void    moveRIGHT(t_frame *img);
void    moveLEFT(t_frame *img);


// utils.c
int     checkWall(char map[HEIGHT][LENGTH], int x, int y);



#endif
