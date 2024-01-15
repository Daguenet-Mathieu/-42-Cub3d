/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2024/01/15 23:19:53 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_minimap(t_minimap mini, t_mlx mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (mini.height))
	{
		j = 0;
		while (j < mini.width)
		{
			if ((unsigned int)mini.map[i * mini.width + j] != TRANSPARENT)
				mlx.image[i * WIDTH + j] = mini.map[i * mini.width + j];
			j++;
		}
		i++;
	}
}

void	get_next_wall(t_env *env)
{
	t_get_next_wall	s;

	ft_memset(&s, 0, sizeof(t_get_next_wall));
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
		print_wall(env, s);
		s.i = s.i - env->map.between_rays;
		s.i_rayon++;
	}
	print_minimap(env->mini, env->mlx);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
