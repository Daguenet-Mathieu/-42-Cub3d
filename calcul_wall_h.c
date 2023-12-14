/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_wall_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:35:08 by auferran          #+#    #+#             */
/*   Updated: 2023/12/08 19:56:12 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_first_intersection_h(t_env *env, double a_p)
{
	double	angle;
	double	t;

	//printf("a_p h = %f\n", a_p);
	angle = ((a_p * M_PI) / 180);
	t = tan(angle);
	//printf("t = %f\n", t);
	env->h.ya = SIZE_CUBE;
	if (a_p >= 0 && a_p <= 179)
	{
		env->h.ya = SIZE_CUBE * -1;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * (SIZE_CUBE) - 0.0001;
	}
	else
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * (SIZE_CUBE) + SIZE_CUBE;
	env->h.new_x = env->map.pixel_x_player + (env->map.pixel_y_player - env->h.new_y) / t;
	env->h.xa = (env->h.ya * -1) / t;
	env->h.grid_y = env->h.new_y / SIZE_CUBE;
	env->h.grid_x = env->h.new_x / SIZE_CUBE;
	//printf("xah = %f\nyah = %f\n", env->h.xa, env->h.ya);
	//printf("new_xh calcul if = %f\nnew_yh calcul if = %f\n", env->h.new_x, env->h.new_y);
	//printf("grid_xh calcul if = %d\ngrid_yh calcul if = %d\n\n", env->h.grid_x, env->h.grid_y);
}

void	check_next_intersection_h(t_env *env)
{
	env->h.new_x += env->h.xa;
	env->h.new_y += env->h.ya;
	env->h.grid_x = env->h.new_x / SIZE_CUBE;
	env->h.grid_y = env->h.new_y / SIZE_CUBE;
	//printf("new_xh calcul while = %f\nnew_yh calcul while = %f\n", env->h.new_x, env->h.new_y);
	//printf("grid_xh calcul while = %d\ngrid_yh calcul while = %d\n\n", env->h.grid_x, env->h.grid_y);
}

void	find_wall_h(t_env *env, double a_p)
{
	check_first_intersection_h(env, a_p);
	if (its_wall(env->map.map, env->h.grid_y, env->h.grid_x))
		return ;
	while (!its_wall(env->map.map, env->h.grid_y, env->h.grid_x))
		check_next_intersection_h(env);
	return ;
}
