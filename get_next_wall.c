/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2024/01/17 08:05:01 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	set_square_minimap(t_minimap minimap, double x, double y)
{
	int	i;
	int	j;
	int	size;
	int	p_x;
	int	p_y;
	int	start[2];
	int *ptr;
	int	*img;
	//int	c;

	size = minimap.height_img * minimap.width_img;
	i = 0;
	//c = 0;
	img = minimap.img;
	ptr = minimap.map;
	//printf("size == %d\n", size);
	while (i < size)
		minimap.img[i++] = 0x0;
	//printf("i == %d\n", i);
	p_x = x / SIZE_CUBE * M_SIZE;
	p_y = y / SIZE_CUBE * M_SIZE;
	start[0] = p_x - minimap.height_img / 2;
	start[1] = p_y - minimap.width_img / 2;
	j = 0;
	//printf("pos x== %d et pos y == %d px == %d et py == %d\n", (int)x/SIZE_CUBE,(int)y/SIZE_CUBE,p_x,p_y);
	//printf("height == %d et width == %d\n", minimap.height_img, minimap.width_img);
	//printf("stat == %det stat == %d\n", start[0], start[1]);
	while (j < minimap.height_img)
	{
		i = 0;
		while (i < minimap.width_img)
		{
			if (start[0] + (j) >= 0 && start[1] + (i) >= 0)
				img[j * minimap.width_img + i] = ptr[(start[0] + j) * minimap.width + (start[1] + i)];
			//else
			//	printf("ici? %d\n", c++);
			i++;
		}
		j++;
	}
	//printf("j == %d\n", j);
	//printf("i == %d\n", i);
}


void	print_mini_player(int *ptr, double p_x, double p_y, t_minimap mini)
{
	// diviser par szecub et multiplier par M_SIZE
//utiliser setcase
	//static int i;
	//printf("i == %d\n", i++);
	//printf("y == %d, x == %d\n", (int)p_y, (int)p_x);
	//printf("y == %d, x == %d\n", (int)p_y/64, (int)p_x/64);
	p_y = (p_y / SIZE_CUBE) * M_SIZE;
	p_x = (p_x / SIZE_CUBE) * M_SIZE;
	//printf("y == %d, x == %d\n", (int)p_y, (int)p_x);
	ptr += (mini.width_img * mini.height_img/2) + (mini.width_img / 2);
	*ptr = 0xffffff;
	*(ptr + 1) = 0xffffff;
	*(ptr + mini.width_img) = 0xffffff;
	*((ptr + mini.width_img) + 1) = 0xffffff;
}

void print_minimap(t_minimap mini, t_mlx mlx)
{
	int	i;
	int	j;
	int	*ptr;

	i = 0;
	ptr = mlx.image + (50 * WIDTH + 50);	
	while (i < (mini.height_img))
	{
		j = 0;
		while (j < mini.width_img)
		{
			if ((unsigned int)mini.map[i * mini.width_img + j] != TRANSPARENT)
				ptr[i * WIDTH + j] = mini.img[i * mini.width_img + j];
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
	set_square_minimap(env->mini,  env->map.pixel_y_player, env->map.pixel_x_player);
	print_mini_player(env->mini.img, env->map.pixel_y_player, env->map.pixel_x_player, env->mini);
	print_minimap(env->mini, env->mlx);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
