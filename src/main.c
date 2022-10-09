/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:31:58 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/17 22:18:47 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[HEIGHT][LENGTH] = 
{
{'0','0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
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
{'1','1','0','0','0','0','0','0','1','1','0','1','0','1','0','1','1','1','1','1','0','1','1','1','1','0','0','0','1','1','1','0','0'},
{'1','1','1','1','0','1','1','1','0','1','1','1','0','1','0','1','0','1','0','1','1','1','1','0','1','0','0','0','1','0','0','0','0'},
{'1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','0'}
};

void	game(t_data *data)
{
	mlx_hook(data->img.window, 3, 1L<<1, keyReleased, &data->img);

	mlx_hook(data->img.window, 2, 1L<<0,  keyPressed, &data->img);
 
	mlx_loop_hook(data->img.mlx, handle_input, data);
}

//	data->img = plan 2d
//	data->img2 = plan3d/affichage (2eme fenetre) 

int main()
{
	t_data data;

	init(&data);

	game(&data);

	mlx_loop(data.img.mlx);
}
