/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2024/01/30 01:31:17 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_weapon(int *image, t_image weapon)
{
	int	start = ((HEIGHT_PLANE - weapon.new_height) * WIDTH) + (((WIDTH / 4) * 3) - (weapon.new_size_line / 2));
	int	size = weapon.new_height * weapon.new_size_line;
	int	i;

	i = 0;
	while (i < size)
	{
		if ((unsigned int)weapon.new_img[i] != 0)
			image[start + (i % weapon.new_size_line)] = weapon.new_img[i];
		i++;
		if (i % weapon.new_size_line == 0)
			start += WIDTH;
	}
}

void	print_crosshair(int *image)
{
	int	i;
	int	j;
	int	center;

	i = 0;
	center = WIDTH * (HEIGHT_PLANE / 2) + (WIDTH / 2);
	j = center - 12;
	while (i < 25)
	{
		if (i < 10 || i > 14)
			image[j] = WHITE;
		j++;
		i++;
	}
	i = 0;
	j = center - (WIDTH * 12);
	while (i < 25)
	{
		if (i < 10 || i > 14)
			image[j] = WHITE;
		j += WIDTH;
		i++;
	}
}

void	get_next_wall_loop(t_get_next_wall *s, t_env *env)
{
	env->h.door_here = 0;
	env->v.door_here = 0;
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
	if (env->h.door_here == 1 || env->v.door_here == 1)
	{
		env->map.distance_door = \
		calcul_distance_door(env, &s->x_door, &s->y_door);
		remove_fishbowl(&env->map.distance_door, s->i);
		s->height_door = \
		(SIZE_CUBE / env->map.distance_door) * env->map.projection_plane;
	}
	recalcul_a_p(&s->a_p, env->map.between_rays);
	print_wall(env, s);
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
	s.i_rayon = 0;
	while (s.i > ((double)POV / 2 * -1))
		get_next_wall_loop(&s, env);
	set_square_minimap(env->mini, env->map.pixel_y_player / SIZE_CUBE, \
	env->map.pixel_x_player / SIZE_CUBE);
	init_circle(env->mini);
	print_mini_player(env->mini.img, env->map.pixel_y_player / \
	SIZE_CUBE, env->map.pixel_x_player / SIZE_CUBE, env->mini);
	print_minimap(env->mini, env->mlx.image, WIDTH);
	print_weapon(env->mlx.image, env->map.gun.cur_img);
	print_crosshair(env->mlx.image);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, \
	env->mlx.s_image, 0, 0);
}
