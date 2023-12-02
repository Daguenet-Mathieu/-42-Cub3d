/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:43:31 by madaguen          #+#    #+#             */
/*   Updated: 2023/12/02 01:16:34 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		get_map(t_map *map, char *file_name)
{
	int		fd;
	char	*line;
	t_lst	*lst;
	
	lst = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (write(2, "ERROR OPEN\n", 12), 0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!add_to_list(line, &lst))
			lst_clear(&lst);
	}
	map->map = lst_to_tab(lst);
	if (!map->map)
		return (write(2, "MALLOC FAILURE\n", 16), 0);
	return (1);
}