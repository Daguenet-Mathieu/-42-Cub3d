#include "cub3D.h"

void	check_first_intersection_h(t_env *env)
{
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle);
	env->h.xa = SIZE_CUBE / t;
	if (env->h.axe_player >= 270 && <= 360 || env->h.axe_player >= 0 && <= 90)
	{
		env->h.ya = SIZE_CUBE;
		env->h.ya = env->map.ya * -1;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * SIZE_CUBE - 1;
	}
	else
	{
		env->h.ya = SIZE_CUBE;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * SIZE_CUBE + SIZE_CUBE;
	}
	env->h.new_x = env->map.pixel_x_player + (env->map->map.pixel_y_player - env->h.new_y) / t;
	env->h.grid_y = env->h.new_y / SIZE_CUBE;
	env->h.grid_x = env->h.new_x / SIZE_CUBE;
}

void	check_next_intersection_h(t_env *env)
{
	env->h.new_x = env->h.old_x + env->h.xa;
	env->h.new_y = env->h.old_y + env->h.ya;
	env->h.grid_x = env->h.new_x / SIZE_CUBE;
	env->h.grid_y = env->h.new_y / SIZE_CUBE;
}

// PAS OUBLIE CODER its_wall

int	find_wall_h(t_env *env)
{
	check_first_intersection_h(env);
	if (its_wall(env->map.wall, env->h.grid_y, env->h.grid_x))
		// return mur trouve
	env->h.old_x = env->h.new_x;
	env->h.old_y = env->h.new_y;
	while (!its_wall(env->map.wall, env->h.grid_y, env->h.grid_x))
	{
		check_next_intersection_h(env);
		env->h.old_x = env->h.new_x;
		env->h.old_y = env->h.new_y;
	}
	// return mur trouve
}
