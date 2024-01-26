/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_wall_v_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:34:56 by auferran          #+#    #+#             */
/*   Updated: 2024/01/26 02:32:04 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_first_intersection_v(t_env *env, double a_p)
{
	double	angle;
	double	t;

	angle = ((a_p * M_PI) / 180);
	t = tan(angle);
	env->v.xa = SIZE_CUBE;
	if (a_p > 90 && a_p < 270)
	{
		env->v.xa = SIZE_CUBE * -1;
		env->v.new_x = \
		floor(env->map.pixel_x_player / SIZE_CUBE) * (SIZE_CUBE) - 0.0001;
	}
	else
		env->v.new_x = \
		floor(env->map.pixel_x_player / SIZE_CUBE) * (SIZE_CUBE) + SIZE_CUBE;
	env->v.new_y = \
	env->map.pixel_y_player + (env->map.pixel_x_player - env->v.new_x) * t;
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
	int	nb;

	check_first_intersection_v(env, a_p);
	while (1)
	{
		nb = its_wall(env->map.map, env->v.grid_y, env->v.grid_x);
		if (nb == 1)
			return ;
		if (nb == 2)
		{
			env->v.grid_x_door = env->v.grid_x;
			env->v.grid_y_door = env->v.grid_y; 
			printf("y = %d\nx= %d\n", env->v.grid_y, env->v.grid_x);
			env->v.y_door = env->v.new_y;
			env->v.x_door = env->v.new_x;
			env->map.door_here = 1;
		}
		check_next_intersection_v(env);
	}
}
