/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:51:11 by antbarbi          #+#    #+#             */
/*   Updated: 2021/10/08 18:58:28 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cpt_words(const char *s, char c)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			cpt++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (s[i])
			i++;
	}
	return (cpt + 1);
}

void	cpt_letters(const char *s, char c, char **tab)
{
	int	i;
	int	cpt;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		cpt = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			cpt++;
			i++;
		}
		tab[j] = (char *)malloc((1 + cpt) * sizeof(char));
		if (!(tab[j]))
			return ;
		if (s[i])
			i++;
		j++;
	}
}

void	assign_tab(const char *s, char c, char **tab)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	x = 0;
	i = 0;
	while (s[x])
	{
		while (s[x] && s[x] != c)
		{
			tab[j][i] = s[x];
			i++;
			x++;
			if (!s[x] || s[x] == c)
			{
				tab[j][i] = '\0';
				i = 0;
				j++;
			}
		}
		while (s[x] && s[x] == c)
			x++;
	}
	tab[j] = 0;
}

char	**ft_split(const char *s, char c)
{
	char	**tab;

	tab = (char **)malloc(cpt_words(s, c) * sizeof(char *));
	if (!(tab))
		return (NULL);
	cpt_letters(s, c, tab);
	assign_tab(s, c, tab);
	return (tab);
}
