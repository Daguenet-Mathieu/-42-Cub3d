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

	if (a_p == 0)
		a_p = 360;
	angle = ((a_p * M_PI) / 180);
	t = tan(angle);
	env->v.xa = SIZE_CUBE;
	if (a_p > 90 && a_p < 270)
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
}

void	check_next_intersection_v(t_env *env)
{
	env->v.new_x += env->v.xa;
	env->v.new_y += env->v.ya;
	env->v.grid_x = env->v.new_x / SIZE_CUBE;
	env->v.grid_y = env->v.new_y / SIZE_CUBE;
}

void	find_wall_v(t_env *env, double a_p)
{
	check_first_intersection_v(env, a_p);
	if (its_wall(env->map.map, env->v.grid_y, env->v.grid_x))
		return ;
	while (!its_wall(env->map.map, env->v.grid_y, env->v.grid_x))
		check_next_intersection_v(env);
}
