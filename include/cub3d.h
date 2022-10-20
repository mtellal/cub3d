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

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include "libft.h"

# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"

# include "macros.h"
# include "types.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////             P A R S I N G                   ///////////////////////////////////////

// init.c
void	init_struct_and_parsing(t_data *data, char *str);

// free_utils.c
void	free_map(t_data *data);
void	free_texture(t_data *data);
void	exit_message(t_data *data, char *str);

//Parsing
void	chck_map_elem(t_data *data);
void	chck_map_edges(t_data *data);
void	check_file_name(t_data *data, char *file);
void	chck_textures(t_data *data);
int		rgb_f(t_data *data, int rgb);
int		rgb_c(t_data *data, int rgb);

void	read_cub(t_data *data, char *path_cub);
int		parse_content(t_data *data, char *line);
int		parse_color(char **texture, char *line, char c);
int		parse_by_id(char **texture, char *line, char *id);
int		parse_map(t_data *data, char *line);

int		ft_maplen(char **map);
int		ft_mapsize(char **map);
int		nb_of_zeros(char **map, char c);

void	stock_player_and_replace(char **map);
void	final_map(t_data *data);

//Todelete
void	print_map(char	**map);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// main.c


//////////////      INIT    //////////////

// init.c
void	init(t_data *img);

// initTriangle.c
void	initTriangle(t_frame *img, int i, int j, char c);

// initImg2D
void	initImg2D(t_data *data, t_frame *img2D);
void	fillImg2D(t_data *data, t_frame *img);


// utils.c
t_coor	coorLine(t_coor point, t_coor origine);
double	getAnlge(t_coor point, t_coor origine);
void	displayCoor(t_coor point);
double	abs_value(double value);
double	getLengthRay(t_coor point, t_coor origine, double angle);
int     checkWall(char map[MHEIGHT][MLENGTH], int x, int y);
void    free_rays(t_ray **rays, int l);

//  exit.c
int     exit_cross(t_data *data);
void	exit_game(t_data *data);
void	exit_game_clean(t_data *data);


/////////////////           DRAW            ///////////////////

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle, int color);
void	draw_wall(t_frame *, int, int);
float barycentre (t_coor p1, t_coor p2, t_coor p3);
int dansLeTriangle (t_coor pt, t_triangle t);



////////////////            RAYS            /////////////////

// rays.c
t_ray	**castRays(t_data *data);
void    cast_and_display(t_data *data);

// horizontal_cast.c
t_coor	firstIntersectionHorizontal(t_coor point, t_coor origine, double angle);
t_coor	horizontalCast(t_data *data, t_coor point, t_coor origine, double angle);


// vertical_cast.c
t_coor	firstIntersectionVertical(t_coor point, t_coor origine, double angle);
t_coor	verticalCast(t_data *data, t_coor point, t_coor origine, double angle);

/////////////// DISPLAY

// displayRays.c
void	displayRays(t_frame *img, double, t_ray **rays, t_texture *texture);

// utils.c
double	correctFishEye(double length, double cumulangle);
t_ray	**initTabRays(double);


////////////////            MOVE            /////////////////

// move.c
void	miniMap(t_data *data, t_frame *minimap, t_frame *img);
void    move(t_data *img);

// movements.c
void    moveUP(t_data *data, t_frame *img, t_coor dda_inc);
void    moveDOWN(t_data *data, t_frame *img, t_coor dda_inc);
void    moveRIGHT(t_data *data, t_frame *img, t_coor dda_inc);
void    moveLEFT(t_data *data, t_frame *img, t_coor dda_inc);

//  vmovements.c
double  deg2rad(double degrees);
double  rad2deg(double radians);
void    rotateTriangle(t_triangle *t, double angle);
void    rrotateTriangle(t_triangle *t, double angle);
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
int keyPressed(int keycode, t_data *data);
int keyReleased(int keycode, t_frame *img);


#endif
