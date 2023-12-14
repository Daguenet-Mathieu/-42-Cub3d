/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_wall_v.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:34:56 by auferran          #+#    #+#             */
/*   Updated: 2023/12/08 19:56:20 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_first_intersection_v(t_env *env, double a_p)
{
	double	angle;
	double	t;

	//printf("a_p v = %f\n", a_p);
	angle = ((a_p * M_PI) / 180);
	t = tan(angle);
	//printf("t = %f\n", t);
	env->v.xa = SIZE_CUBE;
	if (a_p >= 90 && a_p <= 269)
	{
		env->v.xa = SIZE_CUBE * -1;
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * (SIZE_CUBE) - 0.0001;
	}
	else
		env->v.new_x = floor(env->map.pixel_x_player / SIZE_CUBE) * (SIZE_CUBE) + SIZE_CUBE;
	env->v.new_y = env->map.pixel_y_player + (env->map.pixel_x_player - env->v.new_x) * t;
	env->v.ya = (env->v.xa * -1) * t;
	env->v.grid_y = env->v.new_y / SIZE_CUBE;
	env->v.grid_x = env->v.new_x / SIZE_CUBE;
	//printf("xav = %f\nyav = %f\n", env->v.xa, env->v.ya);
	//printf("new_xv calcul if = %f\nnew_yv calcul if = %f\n", env->v.new_x, env->v.new_y);
	//printf("grid_xv calcul if = %d\ngrid_yv calcul if = %d\n\n", env->v.grid_x, env->v.grid_y);
}

void	check_next_intersection_v(t_env *env)
{
	env->v.new_x += env->v.xa;
	env->v.new_y += env->v.ya;
	env->v.grid_x = env->v.new_x / SIZE_CUBE;
	env->v.grid_y = env->v.new_y / SIZE_CUBE;
	//printf("new_xv calcul while = %f\nnew_yv calcul while = %f\n", env->v.new_x, env->v.new_y);
	//printf("grid_xv calcul while = %d\ngrid_yv calcul while = %d\n\n", env->v.grid_x, env->v.grid_y);
}

void	find_wall_v(t_env *env, double a_p)
{
	check_first_intersection_v(env, a_p);
	if (its_wall(env->map.map, env->v.grid_y, env->v.grid_x))
		return ;
	while (!its_wall(env->map.map, env->v.grid_y, env->v.grid_x))
		check_next_intersection_v(env);
}
