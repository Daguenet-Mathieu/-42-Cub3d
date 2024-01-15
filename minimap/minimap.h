/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:17:29 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/15 23:35:43 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define M_SIZE 10
# define HEIGHT_MAP 20
# define WIDTH_MAP 20
# define W 0x545454
# define G 0x00bb77
# define D 0x49311d
# define TRANSPARENT 0xffffffff

# include <stdlib.h>

typedef struct s_minimap
{
	int	*map;
	int	*img;
	int	width;
	int	height;
	int	width_img;
	int	height_img;
	int	radius;
}		t_minimap;

int		create_minimap(t_minimap *minimap, char **map);
void	draw_minimap(t_minimap minimap, char **map);
void	set_square_minimap(t_minimap minimap);
void	set_circle_minimap(t_minimap minimap);
int	ptr_offset(int l, int c, int width, int s_cub);

#endif