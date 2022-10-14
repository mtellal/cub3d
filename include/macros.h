/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:49:04 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/14 13:49:21 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_HPP
#define MACRO_HPP

#define PATHWALL "assets/wall.xpm"

#define GRID 25

// H/L map 
#define MHEIGHT 14
#define MLENGTH 33

// img2D
#define HEIGHT MHEIGHT * GRID
#define LENGTH MLENGTH * GRID

// img3D
#define HEIGHT2 MHEIGHT * 50
#define LENGTH2 MLENGTH * 50

// colors
#define WALLCOLOR 0x00143D3D
#define PLAYERCOLOR 0x0000FFFB

// keycode 
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

#endif
