#include "cub3D.h"

void	check_first_intersection_v(t_env *env)
{
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle);
	env->v.ya = SIZE_CUBE * t;
	if (env->map.axe_player >= 0 && env->map.axe_player <= 179)
	{
		env->v.xa = SIZE_CUBE;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * SIZE_CUBE + SIZE_CUBE;
		printf("if apres floor = %d\n", env->map.pixel_x_player / SIZE_CUBE);
	}
	else
	{
		env->v.xa = SIZE_CUBE;
		env->v.xa = env->v.xa * -1;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * SIZE_CUBE - 1;
		printf("else apres floor = %d\n", env->map.pixel_x_player / SIZE_CUBE);
	}
	printf("av new_yv = %d\nav new_xv = %d\n", env->v.new_y, env->v.new_x);
	env->v.new_y = env->map.pixel_y_player + (env->map.pixel_x_player - env->v.new_x) / t;
	printf("yplayer = %d\nn_x = %d\n", env->map.pixel_y_player, env->v.new_x);
	printf("new_yv = %d\nnew_xv = %d\n", env->v.new_y, env->v.new_x);
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

void	find_wall_v(t_env *env)
{
	printf("new_yh1 = %d\nnew_xh1 = %d\n", env->v.new_y, env->v.new_x);
	check_first_intersection_v(env);
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
