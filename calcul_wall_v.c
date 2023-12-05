#include "cub3D.h"

void	check_first_intersection_v(t_env *env)
{
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle);
	env->v.ya = SIZE_CUBE * t;
	if (env->v.axe_player >= 0 && <= 180)
	{
		env->v.xa = SIZE_CUBE;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * SIZE_CUBE + 64;
	}
	else
	{
		env->v.xa = SIZE_CUBE;
		env->v.xa = env->map.ya * -1;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * 64 - 1;
	}
	env->v.new_y = env->map.pixel_y_player + (env->map->map.pixel_y_player - env->v.new_x) / t;
	env->v.grid_y = env->v.new_y / SIZE_CUBE;
	env->v.grid_x = env->v.new_x / SIZE_CUBE;
}

void	check_next_intersection_v(t_env *env)
{
	env->v.new_x = env->v.old_x + env->v.xa;
	env->v.new_y = env->v.old_y + env->v.ya;
	env->v.grid_x = env->v.new_x / SIZE_CUBE;
	env->v.grid_y = env->v.new_y / SIZE_CUBE;
}

// PAS OUBLIE CODER its_wall

int	find_wall_v(t_env *env)
{
	check_first_intersection_v(env);
	if (its_wall(env->map.wall, env->v.grid_y, env->v.grid_x))
		// return mur trouve
	env->v.old_x = env->v.new_x;
	env->v.old_y = env->v.new_y;
	while (!its_wall(env->map.wall, env->v.grid_y, env->v.grid_x))
	{
		check_next_intersection_h(env);
		env->v.old_x = env->v.new_x;
		env->v.old_y = env->v.new_y;
	}
	// return mur trouve
}
