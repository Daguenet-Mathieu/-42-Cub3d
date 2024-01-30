/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2024/01/29 22:38:30 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_next_wall_loop(t_get_next_wall *s, t_env *env)
{
	if (s->i_rayon == WIDTH - 1)
	{
		s->i = s->i - env->map.between_rays;
		s->i_rayon++;
		return ;
	}
	find_wall_h(env, s->a_p);
	find_wall_v(env, s->a_p);
	env->map.distance_wall = \
	calcul_distance(env, &s->x, &s->y);
	remove_fishbowl(&env->map.distance_wall, s->i);
	s->height = \
	(SIZE_CUBE / env->map.distance_wall) * env->map.projection_plane;
	recalcul_a_p(&s->a_p, env->map.between_rays);
	print_wall(env, *s);
	s->i = s->i - env->map.between_rays;
	s->i_rayon++;
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
		get_next_wall_loop(&s, env);
	set_square_minimap(env->mini, env->map.pixel_y_player / SIZE_CUBE, \
	env->map.pixel_x_player / SIZE_CUBE);
	init_circle(env->mini);
	print_mini_player(env->mini.img, env->map.pixel_y_player / \
	SIZE_CUBE, env->map.pixel_x_player / SIZE_CUBE, env->mini);
	print_minimap(env->mini, env->mlx.image, WIDTH);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, \
	env->mlx.s_image, 0, 0);
}
