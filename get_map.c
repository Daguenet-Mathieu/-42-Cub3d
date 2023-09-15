/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:42:17 by auferran          #+#    #+#             */
/*   Updated: 2023/09/15 20:26:41 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**lst_to_tab(t_lst *lst)
{
	t_lst	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (lst_size(lst) + 1));
	if (!tab)
		return (NULL);
	while (lst)
	{
		tmp = lst->next;
		tab[i] = lst->data;
		free(lst);
		lst = tmp;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**read_map(int fd)
{
	t_lst	*lst;
	char	*line;
	char	**tab;

	line = NULL;
	lst = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)				//GNL echec de malloc vs fin de fichier
			break ;
		add_to_lst(&lst, line);
		if (!lst)
			return (NULL);
	}
	tab = lst_to_tab(lst);
	return (tab);
}

int	get_map(t_map *map, char *map_title)
{
	int	fd;

	fd = open(map_title, O_RDNLY);
	if (fd == -1)
		return (error("OPEN FAILURE\n"), 0);
	close(fd);
	map->map = read_map(fd);
	if (!map->map)
		return (0);
	return (1);
}
