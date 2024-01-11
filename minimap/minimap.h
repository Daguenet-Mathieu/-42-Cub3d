#ifndef MINIMAP_H
#define MINIMAP_H

#include"../cub3D.h"

#define SIZE_MINICUB 10
#define HEIGHT_MAP 200
#define WIDTH_MAP 200

typedef struct s_minimap
{
	int	*map;
	int	*img;
	int width;
	int height;
	int width_img;
	int height_img;
	int radius;
}	t_minimap;

int		create_minimap(t_minimap *, t_map);
void	set_minimap(t_minimap, t_map);
void	set_square_minimap(t_minimap);
void	set_circle_minimap(t_minimap);

#endif