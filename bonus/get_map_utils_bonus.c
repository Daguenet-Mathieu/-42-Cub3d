/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:47:28 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/31 02:12:09 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	atouc(char *nb, int *j)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (nb[i] == 0 || nb[i] == '\n')
		return (-1);
	while (nb[i] == 32 || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	while (nb[i] && nb[i] >= '0' && nb[i] <= '9' && res < 256)
	{
		res = res * 10 + (nb[i] - '0');
		i++;
	}
	if (res >= 256)
		return (-1);
	while (nb[i] == 32 || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	if (i == 0 || (nb[i] != '\0' && nb[i] != ',' && nb[i] == '\n'))
		return (-1);
	if (nb[i] == ',' && nb[i + 1] == ',')
		return (-1);
	*j = *j + i;
	return (res);
}

int	get_color(char *map)
{
	int	color;
	int	rgb;
	int	i;

	color = 0;
	i = 0;
	rgb = atouc(map, &i);
	if (rgb == -1)
		return (-2);
	color += rgb << 16;
	rgb = atouc(map + ++i, &i);
	if (rgb == -1)
		return (-2);
	color += rgb << 8;
	rgb = atouc(map + ++i, &i);
	if (rgb == -1)
		return (-2);
	color += rgb;
	return (color);
}

void	line_check_util(char *line, int i, int *j, char *ret)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		*ret = NO;
	if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		*ret = SO;
	if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]))
		*ret = WE;
	if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]))
		*ret = EA;
	if (*ret)
		*j = i + 2;
}

char	line_check(char *line, int *j)
{
	int		i;
	char	ret;

	i = 0;
	ret = -1;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (line[i] == 'F')
			ret = F;
		else if (line[i] == 'C')
			ret = C;
		*j = i + 1;
	}
	else
		line_check_util(line, i, j, &ret);
	if (line[i] == '\0')
		ret = EMPTY_LINE;
	return (ret);
}

int	verif_dulicate(char verif_line, t_map *map)
{
	if (verif_line == C && map->ceiling != -1)
		return (0);
	else if (verif_line == F && map->floor != -1)
		return (0);
	else if (verif_line == NO && map->no)
		return (0);
	else if (verif_line == SO && map->so)
		return (0);
	else if (verif_line == WE && map->we)
		return (0);
	else if (verif_line == EA && map-> ea)
		return (0);
	return (1);
}
