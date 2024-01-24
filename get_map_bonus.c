/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map _bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:43:31 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/23 22:54:00 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	check_init_elem(t_verif_map *m, t_map *map)
{
	m->verif_line = line_check(m->line, &m->i);
	if (!verif_dulicate(m->verif_line, map))
		return (free(m->line), write(2, "PARSING ERROR\n", 15), 0);
	if (m->verif_line == C)
		map->ceiling = get_color(m->line + m->i);
	else if (m->verif_line == F)
		map->floor = get_color(m->line + m->i);
	else if (m->verif_line == NO)
		map->no = ft_strdup(m->line + m->i);
	else if (m->verif_line == SO)
		map->so = ft_strdup(m->line + m->i);
	else if (m->verif_line == WE)
		map->we = ft_strdup(m->line + m->i);
	else if (m->verif_line == EA)
		map->ea = ft_strdup(m->line + m->i);
	else if (m->verif_line != EMPTY_LINE)
		return (free(m->line), write(2, "PARSING ERROR\n", 15), 0);
	if (map->ceiling == -2 || map->floor == -2)
		return (free(m->line), write(2, "ERROR COLOR\n", 13), 0);
	free(m->line);
	m->line = NULL;
	if (map->ea && map->we && map->no && map->so && map->ceiling != -1 \
	&& map->floor != -1)
		m->done = 1;
	return (1);
}

int	get_map_loop(t_verif_map *m, t_map *map)
{
	m->verif_line = 0;
	m->line = get_next_line(m->fd);
	if (m->line == NULL)
		return (2);
	if (!m->done)
	{
		if (!check_init_elem(m, map))
			return (0);
	}		
	else if (line_check(m->line, &m->i) == EMPTY_LINE)
	{
		free(m->line);
		m->line = NULL;
	}
	else if (!add_to_list(m->line, &m->lst))
		lst_clear(&m->lst);
	m->line = NULL;
	return (1);
}

int	get_map(t_map *map, char *file_name)
{
	t_verif_map	m;
	int			ret;

	m.lst = NULL;
	map->ceiling = -1;
	map->floor = -1;
	m.done = 0;
	m.fd = open(file_name, O_RDONLY);
	m.i = 0;
	if (m.fd == -1)
		return (write(2, "ERROR OPEN\n", 12), 0);
	while (1)
	{
		ret = get_map_loop(&m, map);
		if (ret == 2)
			break ;
		if (!ret)
			return (0);
	}
	map->map = lst_to_tab(m.lst);
	if (!map->map)
		return (write(2, "MALLOC FAILURE\n", 16), 0);
	return (1);
}
