/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 02:14:03 by madaguen          #+#    #+#             */
/*   Updated: 2023/12/02 06:32:50 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	its_player(char c)
{
	int			i;
	const char	*str = "NSEW";

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	init_direction_de_foufurieux(char c, double *axe_player)
{
	if (c == 'N')
		*axe_player = 0;
	if (c == 'E')
		*axe_player = 90;
	if (c == 'S')
		*axe_player = 180;
	if (c == 'W')
		*axe_player = 270;
}

int	check_line(char *line, int *i)
{
	while (line[*i])
	{
		if (its_player(line[*i]))
			return (1);
		(*i)++;
	}
	return (0);
}

void	get_pos_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		if (check_line(map->map[i], &j))
			break ;
		i++;
	}
	map->y_player = i;
	map->x_player = j;
	init_direction_de_foufurieux(map->map[i][j], &map->axe_player);
}
