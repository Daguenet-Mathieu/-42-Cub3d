/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:17:29 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/21 18:32:07 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define M_SIZE 10
# define HEIGHT_MAP 25
# define WIDTH_MAP 25
# define W 0x545454
# define G 0x00bb77
# define D 0x49311d
# define TRANSPARENT 0xffffffff
# define MARGIN 50

# include "stdlib.h"

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

typedef struct s_display_minimap
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;
	int	*ptr;
	int	a;
	int	b;
	int	x;
	int	y;
}	t_display_minimap;

int		create_minimap(t_minimap *minimap, char **map);
void	draw_minimap(t_minimap minimap, char **map);
void	set_square_minimap(t_minimap minimap, double x, double y);
void	set_circle_minimap(t_minimap minimap);
int		ptr_offset(int l, int c, int width, int s_cub);

void	ft_set(void *ptr, int value, int size);
void	set_square_minimap(t_minimap mini, double x, double y);
void	set_circle_minimap(t_minimap mini);
void	init_circle(t_minimap mini);
void	print_mini_player(int *ptr, double p_x, double p_y, t_minimap mini);
void	print_minimap(t_minimap mini, int *ptr, int width);

#endif