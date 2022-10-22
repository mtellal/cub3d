/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:28:34 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/20 12:33:28 by antbarbi         ###   ########.fr       */
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
void    free_rays(t_ray **rays, int l);
void	free_tabs(char **s);
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
void	inittriangle(t_frame *img, int i, int j, char c);

// initImg2D
void	initimg2d(t_data *data, t_frame *img2D);
void	fillimg2d(t_data *data, t_frame *img);

// utils.c
void	displaycoor(t_coor point);
double	abs_value(double value);

//  exit.c
int     exit_cross(t_data *data);
void	exit_game(t_data *data);
void	exit_game_clean(t_data *data);


/////////////////           DRAW            ///////////////////

void    put_pixel(t_frame *img, int x, int y, int color);
void	draw_triangle(t_frame *img, t_triangle triangle, int color);
void	draw_wall(t_frame *, int, int);
float barycentre (t_coor p1, t_coor p2, t_coor p3);
int     dansletriangle (t_coor pt, t_triangle t);



////////////////            RAYS            /////////////////

// rays.c
t_ray	**castrays(t_data *data);
void    cast_and_display(t_data *data);

// cast_a_ray.c
t_coor  castaray(t_data *d, t_coor p, double angle, t_ray *r);

// horizontal_cast.c
t_coor	hor_cast(t_data *data, t_coor point, t_coor origine, double angle);

// vertical_cast.c
t_coor	vert_cast(t_data *data, t_coor point, t_coor origine, double angle);

// utils.c
double	correctfisheye(double length, double cumulangle);
t_ray	**inittabrays(double);
double	getlengthray(t_coor point, t_coor origine, double angle);
t_coor	coorline(t_coor point, t_coor origine);
double	getanlge(t_coor point, t_coor origine);

/////////////// DISPLAY

// displayRays.c
void	displayrays(t_data *data, t_ray **rays);

// displayTextures.c
void	dis_c(t_frame *img3D, int c, t_coor pos, int l);
void	dis_f(t_frame *img3D, int f, t_coor pos, int l);
void	dissw(t_frame *im, t_img *tw, t_drays *drays, double sy);






////////////////            MOVE            /////////////////

// move.c
void	minimap(t_data *data, t_frame *minimap, t_frame *img);
void    move(t_data *img);

// movements.c
void    moveup(t_data *data, t_frame *img, t_coor dda_inc);
void    movedown(t_data *data, t_frame *img, t_coor dda_inc);
void    moverigth(t_data *data, t_frame *img, t_coor dda_inc);
void    moveleft(t_data *data, t_frame *img, t_coor dda_inc);

// movements_utils.c
void	addpixelx(t_triangle *t, double pixel);
void	addpixely(t_triangle *t, double pixel);
int     checkpointwall(t_data *data, t_coor point, t_coor dda_inc);
int     checkcoorsquare(t_data *data, t_coor c1, t_coor c2, t_coor dda_inc);

// radians_deg.c
double  deg2rad(double degrees);
double  rad2deg(double radians);

//  vmovements.c
void    rotatetriangle(t_triangle *t, double angle);
void    rrotatetriangle(t_triangle *t, double angle);
void    movevrigth(t_frame *img);
void    movevleft(t_frame *img);


//  rotate.c
double      rotatex(double angle, double x, double y, int r);
double      rotatey(double angle, double x, double y, int r);
void        rotatepoint(double angle, double *x, double *y, t_coor origine);
void        rrotatepoint(double angle, double *x, double *y, t_coor origine);


///////////////         EVENTS             ////////////////

//events.c
int	handle_input(void *img);
int keypressed(int keycode, t_data *data);
int keyreleased(int keycode, t_frame *img);


#endif
