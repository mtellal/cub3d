/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:12:47 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/03 15:22:36 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_xpm_file(int fd)
{
	int		i;
	char	c;
	char	*s;

	i = 0;
	s = "/* XPM */";
	c = 0;
	while (i < 9)
	{
		if (read(fd, &c, 1) != -1 && c == s[i])
			i++;
		else
		{
			close(fd);
			return (0);
		}
	}
	return (1);
}
