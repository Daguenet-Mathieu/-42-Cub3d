#include "cub3D.h"

int	its_wall(char **map, int grid_y, int grid_x)
{
	printf("y = %d\nx = %d\n", grid_y, grid_x);
	if (map[grid_y][grid_x] == '1')
		return (1);
	return (0);
}