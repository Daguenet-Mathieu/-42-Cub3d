#include "cub3D.h"

void	check_first_intersection_h(t_env *env)
{
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle);
	env->h.xa = SIZE_CUBE / t;
	if ((env->map.axe_player >= 270 && env->map.axe_player <= 359) || (env->map.axe_player >= 0 && env->map.axe_player <= 89))
	{
		env->h.ya = SIZE_CUBE;
		env->h.ya = env->h.ya * -1;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * SIZE_CUBE - 1;
		printf("if apres floor = %d\n", env->map.pixel_y_player / SIZE_CUBE);
	}
	else
	{
		env->h.ya = SIZE_CUBE;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * SIZE_CUBE + SIZE_CUBE;
		printf("else apres floor = %d\n", env->map.pixel_y_player / SIZE_CUBE);
	}
	env->h.new_x = env->map.pixel_x_player + (env->map.pixel_y_player - env->h.new_y) / t;
	printf("new_yh = %d\nnew_xh = %d\n", env->h.new_y, env->h.new_x);
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

void	find_wall_h(t_env *env)
{
	printf("new_yh1 = %d\nnew_xh1 = %d\n", env->h.new_y, env->h.new_x);
	check_first_intersection_h(env);
	if (its_wall(env->map.map, env->h.grid_y, env->h.grid_x))
		return ;
	env->h.old_x = env->h.new_x;
	env->h.old_y = env->h.new_y;
	while (!its_wall(env->map.map, env->h.grid_y, env->h.grid_x))
	{
		check_next_intersection_h(env);
		env->h.old_x = env->h.new_x;
		env->h.old_y = env->h.new_y;
	}
	return ;
}
