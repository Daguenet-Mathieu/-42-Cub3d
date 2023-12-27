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

int	get_pixel(t_env *env, double ratio_leon, double column_texture, int i)
{
	double	j;
	double	tmp;
	double	pixel;

	j = env->map.diff * env->map.texture_no.size_line;
	j += (i * env->map.texture_no.size_line * ratio_leon);
	tmp = (int)j % env->map.texture_no.size_line;
	j -= tmp;
	pixel = j + column_texture;
	return (env->map.img[(int)pixel]);
}

void	print_wall(t_env *env, double height, int x, int y, int i_rayon)
{
	int	i;
	double	height_draw;
	double	index_img;
	double	ratio_leon;
	double	column_texture;
	int		orientation;
	int		y_start;

	env->map.img = env->map.texture_no.img;
	if (x > -1)
	{
		if ((int)env->map.pixel_x_player > x)
			orientation = WEST;
		else
			orientation = EAST;
		index_img = fmod(env->v.new_y, SIZE_CUBE);
	}
	if (y > -1)
	{
		if ((int)env->map.pixel_y_player > y)
			orientation = NORTH;
		else
			orientation = SOUTH;
		index_img = fmod(env->h.new_x, SIZE_CUBE);
	}
	i = 0;
	ratio_leon = env->map.texture_no.height / height;
	column_texture = index_img * (double)env->map.texture_no.height / (double)SIZE_CUBE;
	height_draw = height;
	if (height_draw > HEIGHT_PLANE)
	{
		height_draw = HEIGHT_PLANE;
		env->map.diff = (height - height_draw) / (height / height_draw * 2);
	}
	y_start = (HEIGHT_PLANE / 2) - (height_draw / 2);
	while (i < (int)height_draw)
	{
		if (orientation == NORTH)
		{
			env->mlx.image[((y_start + i) * WIDTH) + i_rayon] = get_pixel(env, ratio_leon, column_texture, i);
			i++;
		}
		else
		{
			env->mlx.image[((y_start + i) * WIDTH) + i_rayon] = orientation;
			i++;
		}
	}
	env->map.diff = 0;
}

void	get_next_wall(t_env *env)
{
	int		x;
	int		y;
	double	i;
	double	a_p;
	double	hauteur_tranche;
	int		i_rayon;

	env->map.projection_plane = calcul_projection_plane();
	env->map.between_rays = (double)POV / (double)WIDTH;
	a_p = calcul_a_p(env->map.axe_player);
	i = POV / 2;
	i_rayon = 1;
	while (i > ((double)POV / 2 * -1))
	{
		x = -1;
		y = -1;
		find_wall_h(env, a_p);
		find_wall_v(env, a_p);
		env->map.distance_wall = calcul_distance(env, &x, &y);
		//printf("x = %d\n", x);
		//printf("y = %d\n", y);
		remove_fishbowl(&env->map.distance_wall, i);
		hauteur_tranche = (SIZE_CUBE / env->map.distance_wall) * env->map.projection_plane;
		//if (hauteur_tranche > HEIGHT_PLANE)
		//	hauteur_tranche = HEIGHT_PLANE;
		recalcul_a_p(&a_p, env->map.between_rays);
		i = i - env->map.between_rays;
		i_rayon++;
		print_wall(env, hauteur_tranche, x, y, i_rayon);
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
