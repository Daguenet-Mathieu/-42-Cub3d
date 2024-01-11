#include "minimap.h"

void	set_minimap(t_minimap mini, t_map map)
{

}

int	create_minimap(t_minimap *mini, t_map map)
{
	mini->width = map.x_max * SIZE_MINICUB;
	mini->height = map.y_max * SIZE_MINICUB;
	mini->width_img = WIDTH_MAP * SIZE_MINICUB;
	mini->height_img = HEIGHT_MAP * SIZE_CUBE;
	if (mini->width_img > mini->width)
		mini->width_img = mini->width;
	if (mini->height_img > mini->height)
		mini->height_img = mini->height;
	mini->map = malloc(sizeof(int) * (mini->width * mini->height));
	if (!mini->map)
		return (0);
	mini->img = malloc(sizeof(int) * (mini->width_img * mini->height_img));
	if (!mini->img)
		return (free(mini->map), 0);
	return (1);
}
