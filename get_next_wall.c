/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:34:49 by auferran          #+#    #+#             */
/*   Updated: 2023/12/08 19:55:40 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_wall(t_env *env, double height, int x, int y, int i_rayon)
{
	int	i;
	int	index_img;
	int	orientation;
	int	y_start;
	static int w;
	(void) w;

	if (x > -1)
	{
		if ((int)env->map.pixel_x_player > x)
			orientation = WEST;
		else
			orientation = EAST;
		index_img = x % 64;
	}
	else
	{
		if ((int)env->map.pixel_y_player > y)
			orientation = SOUTH;
		else
			orientation = NORTH;
		index_img = y % 64;
	}
	i = 0;
	y_start = (HEIGHT_PLANE / 2) - (height / 2);
	//printf("height = %d\n", (int)height);
	//printf("w = %d\n", w++);
	while (i < (int)height)
	{
		//printf("= %d\n", (y_start + i) * WIDTH + i_rayon);
		env->mlx.image[((y_start + i) * WIDTH) + i_rayon] = orientation; //a termes ce sera index_ing dans image
		i++;
	}
}

void	get_next_wall(t_env *env)
{
	int		x;
	int		y;
	double	i;
	double	a_p;
	double	distance;
	double	hauteur_tranche;
	double	i_angle;
	int		i_rayon;

	(void)distance;
	(void)hauteur_tranche;
	env->map.projection_plane = calcul_projection_plane();
	env->map.between_rays = (double)POV / (double)WIDTH;
	a_p = calcul_a_p(env->map.axe_player);
	i = POV / 2;
	i_angle = 1;
	x = -1;
	y = -1;
	i_rayon = 1;
	while (i > ((double)POV / 2 * -1))
	{
		find_wall_h(env, a_p, i_angle);
		find_wall_v(env, a_p, i_angle);
		distance = calcul_distance(env, &x, &y);
		remove_fishbowl(&distance, i);
		hauteur_tranche = (SIZE_CUBE / distance) * env->map.projection_plane;
		recalcul_a_p(&a_p, env->map.between_rays);
		i = i - env->map.between_rays;
		i_angle = i_angle + env->map.between_rays;
		i_rayon++;
		print_wall(env, hauteur_tranche, x, y, i_rayon);
	}
}
