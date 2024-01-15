/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:43:31 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/15 23:40:51 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int atouc(char *nb, int *j)
{
	int i;
	int res;

	i = 0;
	res = 0;
	//printf("line == %s\n", nb);
	while (nb[i] == 32 || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	while (nb[i] && nb[i] >= '0' && nb[i] <= '9' && res < 256)
	{
		res = res * 10 + (nb[i] - '0');
		i++;
	}
	//printf("char == %d, i == %d\n", res, i);
	if (res >= 256)
		return (-1);

	//printf("1\n");
	while (nb[i] == 32 || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	//printf("2, %s\n", nb+i);
	if (nb[i] != '\0' && nb[i] != ',' && nb[i] == '\n')
		return (-1);
	if (nb[i] == ',' && nb[i + 1] == ',')
		return (-1);
	//printf("3\n");
	*j = *j + i;
	//printf("char === %c i == %d\n",nb[i], i);
	return (res);
}

int get_color(char *map)
{
	int color;
	int rgb;
	int i;

	color = 0;
	i = 0;
	rgb = atouc(map, &i);
	if (rgb == -1)
		return (-2);
	color += rgb<<16;
	//printf("i == %d\n", i);
	rgb = atouc(map + i + 1, &i);
	if (rgb == -1)
		return (-2);
	color += rgb<<8;
	//printf("rgb == %d\n", rgb);
	//printf("i == %d\n", i);
	//printf("color == %x\n", color);
	rgb = atouc(map + i + 2, &i);
	if (rgb == -1)
		return (-2);
	//printf("rgb == %d\n", rgb);
	//printf("i == %d\n", i);
	//printf("color == %x\n", color);
	color += rgb;
	//printf("rgb == %d\n", rgb);
	//printf("color == %x\n", color);
	return (color);
}

char line_check(char *line, int *j)
{
	int i;
	char ret;

	i = 0;
	ret = -1;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
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
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')//check white space
			ret = NO;
		if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			ret = SO;
		if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			ret = WE;
		if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
			ret = EA;
		if (ret)
			*j = i + 2;
	}
	if (line[i] == '\0')
		ret = EMPTY_LINE;
	return (ret);
}

char *ft_strdup(const char *str)
{
	int	i;
	int	j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(ft_strlen((char *)str) + 1);
	while (str[j] == 32 || (str[j] <= 13 && str[j] >= 9))
		j++;
	while (str[j] && str[j] != '\n')
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = 0;
	return (new);
}

int		get_map(t_map *map, char *file_name)
{
	int		fd;
	char	*line;
	t_lst	*lst;
	int		done;
	char	verif_line;
	int 	i;

	lst = NULL;
	map->ceiling = -1;
	map->floor = -1;
	done = 0;
	fd = open(file_name, O_RDONLY);
	i = 0;
	if (fd == -1)
		return (write(2, "ERROR OPEN\n", 12), 0);
	while (1)
	{
		verif_line = 0;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!done)
		{
			verif_line = line_check(line, &i);
			if (verif_line == C)
				map->ceiling = get_color(line + i);
			else if (verif_line == F)
				map->floor = get_color(line + i);
			else if (verif_line == NO)
				map->no = ft_strdup(line + i);
			else if (verif_line == SO)
				map->so = ft_strdup(line + i);
			else if (verif_line == WE)
				map->we = ft_strdup(line + i);
			else if (verif_line == EA)
				map->ea = ft_strdup(line + i);
			else if (verif_line != EMPTY_LINE)
				return (free(line), write(2, "PARSING ERROR\n", 15),0);
			if (map->ceiling == -2 || map->floor == -2)
				return (free(line), write(2, "ERROR COLOR\n", 13), 0);
			free(line);
			line = NULL;
			if (map->ea && map->we && map->no && map->so && map->ceiling != -1 && map->floor !=-1)
				done = 1;
		}
		else if (line_check(line, &i) == EMPTY_LINE)
		{
			free(line);
			line = NULL;
		}
		else if (!add_to_list(line, &lst))
			lst_clear(&lst);
		printf("line == %s\n", line);
		line = NULL;
	}
	map->map = lst_to_tab(lst);
	if (!map->map)
		return (write(2, "MALLOC FAILURE\n", 16), 0);
	return (1);
}
