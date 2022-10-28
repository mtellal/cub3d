/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:33:04 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/29 18:18:24 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*chck_texture_id(char *id, char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] == id[0] && line[i + 1] == id[1])
		{
			found = 1;
			i++;
		}
		else if (found && line[i] != ' ')
			return (line + i);
		i++;
	}
	return (NULL);
}

char	*chck_fc_color(char c, char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] == c)
			found = 1;
		else if (found && line[i] != 32)
			return (line + i);
		i++;
	}
	return (NULL);
}

int	parse_by_id(char **texture, char *line, char *id)
{
	char		*ptr;
	int			i;

	i = 0;
	ptr = chck_texture_id(id, line);
	if (!ptr)
		return (0);
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
		i++;
	*texture = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
	{
		texture[0][i] = ptr[i];
		i++;
	}
	texture[0][i] = '\0';
	while (ptr[i])
	{
		if (ptr[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	parse_color(char **texture, char *line, char c)
{
	char		*ptr;
	int			i;

	i = 0;
	ptr = chck_fc_color(c, line);
	if (!ptr)
		return (0);
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
		i++;
	*texture = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
	{
		texture[0][i] = ptr[i];
		i++;
	}
	texture[0][i] = '\0';
	while (ptr[i])
	{
		if (ptr[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
