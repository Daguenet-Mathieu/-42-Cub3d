#include "cub3D.h"

int	its_wall(char **map, int grid_y, int grid_x)
{
	if (map[grid_y][grid_x] == '1')
		return (1);
	return (0);
}

double	calcul_projection_plane(void)
{
	double	nb;
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle / 2);
	nb = (WIDTH / 2) / t;
	return (nb);
}

double	calcul_a_p(double axe_player)
{
	double	a_p;
	double	tmp;

	if (axe_player < 30)
	{
		tmp = 30 - axe_player;
		a_p = 360 - tmp;
	}
	else
		a_p = axe_player - 30;
	return (a_p);
}

void	recalcul_a_p(double *a_p, double between_rays)
{
	*a_p = *a_p + between_rays;
	if (*a_p > 359)
		*a_p = *a_p - 359;
}

double	calcul_distance(t_env *env)
{
	double			d;
	double			d_h;
	double			d_v;

	d_h = sqrt(pow((double)env->map.pixel_x_player - (double)env->h.new_x, 2)
		+ pow((double)env->map.pixel_y_player - (double)env->h.new_y, 2));
	d_v = sqrt(pow((double)env->map.pixel_x_player - (double)env->v.new_x, 2)
		+ pow((double)env->map.pixel_y_player - (double)env->v.new_y, 2));
	if (d_h <= d_v)
		d = d_h;
	else
		d = d_v;
	return (d);
}
