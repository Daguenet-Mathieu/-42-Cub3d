/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2023/12/14 21:19:49 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

void	print_wall(t_env *env, double height, int x, int y, int i_rayon)
{
	int	i;
	int	index_img;
	int	orientation;
	int	y_start;
	(void) index_img;
	//static int n;

	//printf("nb call == %d, height == %f\n", n++, height);
	if (x > -1)
	{
		if ((int)env->map.pixel_x_player > x)
			orientation = EAST;
		else
			orientation = WEST;
		index_img = x % 64;
	}
	else
	{
		if ((int)env->map.pixel_y_player > y)
			orientation = NORTH;
		else
			orientation = SOUTH;
		index_img = y % 64;
	}
	i = 0;
	if (height > HEIGHT_PLANE)
		height = HEIGHT_PLANE;
	y_start = (HEIGHT_PLANE / 2) - (height / 2);
	//printf("height = %d\n", (int)height);
	//printf("w = %d\n", w++);
	while (i < (int)height)
	{
		//printf("= %d\n", (y_start + i) * WIDTH + i_rayon);
		env->mlx.image[((y_start + i) * WIDTH) + i_rayon] = orientation; //a termes ce sera index_img dans image
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
	int		i_rayon;

	env->map.projection_plane = calcul_projection_plane();
	env->map.between_rays = (double)POV / (double)WIDTH;
	a_p = calcul_a_p(env->map.axe_player);
	i = POV / 2;
	x = -1;
	y = -1;
	i_rayon = 1;
	while (i > ((double)POV / 2 * -1))
	{
		//printf("player_x = %f\nplayer_y = %f\n", env->map.pixel_x_player, env->map.pixel_y_player);
		//printf("i_rayon = %d\n", i_rayon);
		//printf("axe_player = %f\n", env->map.axe_player);
		//printf("y_player = %f\nx_player = %f\n", env->map.pixel_y_player, env->map.pixel_x_player);
		find_wall_h(env, a_p);
		find_wall_v(env, a_p);
		//printf("new_xh = %f\nnew_yh = %f\n", env->h.new_x, env->h.new_y);
		//printf("new_xv = %f\nnew_yv = %f\n\n", env->v.new_x, env->v.new_y);
		distance = calcul_distance(env, &x, &y);
		remove_fishbowl(&distance, i);
		//printf("distance = %f\n", distance);
		//printf("env->map.projection_plane = %f\n", env->map.projection_plane);
		hauteur_tranche = SIZE_CUBE / distance * env->map.projection_plane;
		//printf("hauteur_tranche = %f\n", hauteur_tranche);
		hauteur_tranche = (SIZE_CUBE / distance) * env->map.projection_plane;
		if (hauteur_tranche > HEIGHT_PLANE)
			hauteur_tranche = HEIGHT_PLANE;
		//printf("projection plane = %f\n", env->map.projection_plane);
		//printf("hauteur_tranche = %f\n", hauteur_tranche);
		recalcul_a_p(&a_p, env->map.between_rays);
		i = i - env->map.between_rays;
		i_rayon++;
		print_wall(env, hauteur_tranche, x, y, i_rayon);
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
