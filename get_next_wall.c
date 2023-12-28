/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2023/12/19 10:37:32 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_next_wall(t_env *env)
{
	t_get_next_wall	s;

	env->map.projection_plane = calcul_projection_plane();
	env->map.between_rays = (double)POV / (double)WIDTH;
	s.a_p = calcul_a_p(env->map.axe_player);
	s.i = POV / 2;
	s.i_rayon = 1;
	while (s.i > ((double)POV / 2 * -1))
	{
		s.x = -1;
		s.y = -1;
		find_wall_h(env, s.a_p);
		find_wall_v(env, s.a_p);
		env->map.distance_wall = calcul_distance(env, &s.x, &s.y);
		remove_fishbowl(&env->map.distance_wall, s.i);
		s.height = (SIZE_CUBE / env->map.distance_wall) * env->map.projection_plane;
		recalcul_a_p(&s.a_p, env->map.between_rays);
		s.i = s.i - env->map.between_rays;
		s.i_rayon++;
		print_wall(env, s);
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
