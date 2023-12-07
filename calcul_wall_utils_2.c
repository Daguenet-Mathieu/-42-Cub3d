#include "cub3D.h"

void	remove_fishbowl(double *distance, double i)
{
	double	c;
	double	tmp;
	double	angle;

	angle = ((i * M_PI) / 180);
	c = cos(angle);
	tmp = *distance;
	*distance = tmp * c;
}
