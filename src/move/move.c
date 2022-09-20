/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:17:02 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/20 09:17:11 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	map[14][35] = 
{
{'0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
{'0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'0','0','0','0','0','0','0','0','1','0','1','1','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'1','1','1','1','1','1','1','1','1','0','1','1','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
{'1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1'},
{'1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'},
{'1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1','0','1','0','0','1','0','0','0','1','0','0','0','0'},
{'1','1','0','0','0','0','0','0','1','1','0','1','0','1','0','1','1','1','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'},
{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','1','0','0','0','1','0','0','0','0'},
{'1','0','0','0','0','0','0','N','0','0','0','0','0','0','0','0','1','1','0','1','0','1','0','0','1','0','0','0','1','0','0','0','0'},
{'1','1','0','0','0','0','0','1','1','1','0','1','0','1','0','1','1','1','1','1','0','1','1','1','1','0','0','0','1','1','1','0','0'},
{'1','1','1','1','0','1','1','1','0','1','1','1','0','1','0','1','0','1','0','1','1','1','1','0','1','0','0','0','1','0','0','0','0'},
{'1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','0'}
};

void    refillWalls(t_frame *img, char map[14][35])
{
    int i = 0;
	int j = 0;
	t_wall	w;

	w.size = 20;
	w.color = 0x00B0FF00;

	while (i < HEIGHT)
	{
		j = 0;
		while (j < LENGTH)
		{
			if (map[i][j] == '1')
                draw_wall(img, w, i * w.size, j * w.size);
            j++;
		}
		i++;
	}
}

int     checkWall(char map[HEIGHT][LENGTH], int x, int y)
{
    if (map[x][y] == '1')
        return (1);
    return (0);
}

///////// MOVEMENTS /////////////

void    moveUP(t_frame *img)
{
    if (img->triangle.a.y - 5 > 0 &&
        img->triangle.b.y - 5 > 0 &&
        img->triangle.c.y - 5 > 0 && 
            !checkWall(map, (img->triangle.ipos.x - 5) / 20, (img->triangle.ipos.y + 10) / 20))
    {

        img->triangle.a.y -= 5;
        img->triangle.b.y -= 5;
        img->triangle.c.y -= 5;
        img->triangle.milieu.y -= 5;
        img->triangle.ipos.x -= 5;
    }
}

void    moveDOWN(t_frame *img)
{
    if (img->triangle.milieu.y + 5 < HEIGHT * 20 && 
            !checkWall(map, (img->triangle.ipos.x  + 20 )/ 20, (img->triangle.ipos.y + 10) / 20))
    {
        img->triangle.a.y += 5;
        img->triangle.b.y += 5;
        img->triangle.c.y += 5;
        img->triangle.milieu.y += 5;
        img->triangle.ipos.x += 5;
    }
}

void    moveRIGHT(t_frame *img)
{
    if (img->triangle.c.x + 5 < LENGTH * 20 && 
            !checkWall(map, (img->triangle.ipos.x + 10) / 20, (img->triangle.ipos.y + 20) / 20))
    {
        img->triangle.a.x += 5;
        img->triangle.b.x += 5;
        img->triangle.c.x += 5;
        img->triangle.milieu.x += 5;
        img->triangle.ipos.y += 5;
    }
}

void    moveLEFT(t_frame *img)
{
    if (img->triangle.b.x >= 0 && 
            !checkWall(map, (img->triangle.ipos.x + 10) / 20, (img->triangle.ipos.y - 5) / 20))
    {
        img->triangle.a.x -= 5;
        img->triangle.b.x -= 5;
        img->triangle.c.x -= 5;
        img->triangle.milieu.x -= 5;
        img->triangle.ipos.y -= 5;
    }
}

//////////////  VMOVEMENTS  //////

void    moveVRIGHT(t_frame *img)
{
    double  angle = 10;

    double	apos_x = img->triangle.milieu.x - img->triangle.a.x;
    double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

    img->triangle.a.x = (apos_x * cos(angle)) + (apos_y * -sin(angle));
    img->triangle.a.x += img->triangle.milieu.x;

    img->triangle.a.y = (apos_x * sin(angle)) + (apos_y* cos(angle));
    img->triangle.a.y += img->triangle.milieu.y;


    double	bpos_x = img->triangle.milieu.x - img->triangle.b.x;
    double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

    img->triangle.b.x = (bpos_x * cos(angle)) + (bpos_y * -sin(angle));
    img->triangle.b.x += img->triangle.milieu.x;

    img->triangle.b.y = (bpos_x * sin(angle)) + (bpos_y * cos(angle));
    img->triangle.b.y += img->triangle.milieu.y;


    double	cpos_x = img->triangle.milieu.x - img->triangle.c.x;
    double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

    img->triangle.c.x = (cpos_x * cos(angle)) + (cpos_y * -sin(angle));
    img->triangle.c.x += img->triangle.milieu.x;

    img->triangle.c.y = (cpos_x * sin(angle)) + (cpos_y* cos(angle));
    img->triangle.c.y += img->triangle.milieu.y;
}

void    movevLEFT(t_frame *img)
{
    double		angle = 100;

    double	apos_x = img->triangle.milieu.x - img->triangle.a.x;
    double	apos_y = img->triangle.milieu.y - img->triangle.a.y;

    img->triangle.a.x = (apos_x * -cos(angle)) + (apos_y * sin(angle));
    img->triangle.a.x += img->triangle.milieu.x;

    img->triangle.a.y = (apos_x * -sin(angle)) + (apos_y* -cos(angle));
    img->triangle.a.y += img->triangle.milieu.y;


    double	bpos_x = img->triangle.milieu.x - img->triangle.b.x;
    double	bpos_y = img->triangle.milieu.y - img->triangle.b.y;

    img->triangle.b.x = (bpos_x * -cos(angle)) + (bpos_y * sin(angle));
    img->triangle.b.x += img->triangle.milieu.x;

    img->triangle.b.y = (bpos_x * -sin(angle)) + (bpos_y * -cos(angle));
    img->triangle.b.y += img->triangle.milieu.y;


    double	cpos_x = img->triangle.milieu.x - img->triangle.c.x;
    double	cpos_y = img->triangle.milieu.y - img->triangle.c.y;

    img->triangle.c.x = (cpos_x * -cos(angle)) + (cpos_y * sin(angle));
    img->triangle.c.x += img->triangle.milieu.x;

    img->triangle.c.y = (cpos_x * -sin(angle)) + (cpos_y* -cos(angle));
    img->triangle.c.y += img->triangle.milieu.y;
}

int	moove(int keycode, t_frame *img)
{
    int     i;
    int     movements[6] = {UP, DOWN, RIGHT,  LEFT, VRIGHT, VLEFT};
    void    (*move[6])(t_frame *img) = {
        moveUP,
        moveDOWN,
        moveRIGHT,
        moveLEFT,
        moveVRIGHT,
        movevLEFT
    };

    i = 0;

	new_frame(img);

    while (i < 6)
    {
        if (keycode == movements[i])
            move[i](img);
        i++;
    }

	draw_triangle(img, img->triangle);
    refillWalls(img, map);
	push_frame(img);
    
	return (0); 
} 

