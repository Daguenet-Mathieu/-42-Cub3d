#include "cub3D.h"

void	check_first_intersection_v(t_env *env, double a_p)
{
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle);
	env->v.ya = SIZE_CUBE * t;
	if (a_p >= 0 && a_p <= 179)
	{
		env->v.xa = SIZE_CUBE;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * SIZE_CUBE + SIZE_CUBE;
	}
	else
	{
		env->v.xa = SIZE_CUBE * -1;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * SIZE_CUBE - 1;
	}
	env->v.new_y = env->map.pixel_y_player + (env->map.pixel_x_player - env->v.new_x);
	env->v.new_y = env->v.new_y * t;
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

void	find_wall_v(t_env *env, double a_p)
{
	check_first_intersection_v(env, a_p);
	if (its_wall(env->map.map, env->v.grid_y, env->v.grid_x))
		return ;
	env->v.old_x = env->v.new_x;
	env->v.old_y = env->v.new_y;
	while (!its_wall(env->map.map, env->v.grid_y, env->v.grid_x))
	{
		check_next_intersection_v(env);
		env->v.old_x = env->v.new_x;
		env->v.old_y = env->v.new_y;
	}
}
