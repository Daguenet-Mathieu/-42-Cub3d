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

void	check_first_intersection_h(t_env *env, double a_p, double i)
{
	double	angle;
	double	t;
	(void)	i;

	angle = ((POV * M_PI) / 180);
	t = tan(angle);
	env->h.xa = SIZE_CUBE / t;
	if ((a_p >= 270 && a_p <= 359) || (a_p >= 0 && a_p <= 89))
	{
		env->h.ya = SIZE_CUBE * -1;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * SIZE_CUBE - 1;
	}
	else
	{
		env->h.ya = SIZE_CUBE;
		env->h.new_y = floor(env->map.pixel_y_player / SIZE_CUBE) * SIZE_CUBE + SIZE_CUBE;
	}
	env->h.new_x = env->map.pixel_x_player + (env->map.pixel_y_player - env->h.new_y);
	env->h.new_x = env->h.new_x / t;
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

void	find_wall_h(t_env *env, double a_p, double i)
{
	check_first_intersection_h(env, a_p, i);
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
