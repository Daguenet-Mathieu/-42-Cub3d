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

int	get_pixel(double ratio_leon, int column, int i, int	*img)
{
	int	pixel;
	(void) column;
	(void) ratio_leon;
	pixel = i + column;
	return (img[pixel]);
}

void	print_wall(t_env *env, double height, int x, int y, int i_rayon)
{
	int	i;
	double	index_img;
	int		orientation;
	int		y_start;
	int		*img;
	double		column;
	double	ratio_leon;

	img = env->map.texture_no.img;
	if (x > -1)
	{
		if ((int)env->map.pixel_x_player > x)
			orientation = WEST;
		else
			orientation = EAST;
		index_img = (int)env->v.new_y % SIZE_CUBE;
	}
	if (y > -1)
	{
		if ((int)env->map.pixel_y_player > y)
			orientation = NORTH;
		else
			orientation = SOUTH;
		index_img = (int)env->h.new_x % SIZE_CUBE;
	}
	i = 0;
	if (height > HEIGHT_PLANE)
		height = HEIGHT_PLANE;
	y_start = (HEIGHT_PLANE / 2) - (height / 2);
	ratio_leon = env->map.texture_no.height / height;
	// printf("env->h.new_x = %f\n", env->h.new_x);
	// printf("index_img = %f\n", index_img);
	// printf("no.height = %d\n", env->map.texture_no.height);
	// printf("height = %f\n", height);
	// printf("ratio_leon = %f\n", ratio_leon);
	column = env->map.texture_no.size_line * index_img / SIZE_CUBE;
	column *= ratio_leon;
	//printf("index_img = %f\n", index_img);
	//printf("column = %d\n\n", column);
	//printf("column = %f\n", column);
	while (i < (int)height)
	{
		if (orientation == NORTH)
		{
			env->mlx.image[((y_start + i) * WIDTH) + i_rayon] = get_pixel(ratio_leon, column, i * env->map.texture_no.size_line * ratio_leon, img);
			i++;
		}
		else
		{
			env->mlx.image[((y_start + i) * WIDTH) + i_rayon] = orientation; //a termes ce sera index_img dans image
			i++;
		}
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
	i_rayon = 1;
	while (i > ((double)POV / 2 * -1))
	{
		x = -1;
		y = -1;
		find_wall_h(env, a_p);
		find_wall_v(env, a_p);
		distance = calcul_distance(env, &x, &y);
		//printf("x = %d\n", x);
		//printf("y = %d\n", y);
		remove_fishbowl(&distance, i);
		hauteur_tranche = (SIZE_CUBE / distance) * env->map.projection_plane;
		if (hauteur_tranche > HEIGHT_PLANE)
			hauteur_tranche = HEIGHT_PLANE;
		recalcul_a_p(&a_p, env->map.between_rays);
		i = i - env->map.between_rays;
		i_rayon++;
		print_wall(env, hauteur_tranche, x, y, i_rayon);
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
