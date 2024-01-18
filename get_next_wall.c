/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:04:12 by auferran          #+#    #+#             */
/*   Updated: 2024/01/19 00:01:39 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	set_square_minimap(t_minimap mini, double x, double y)
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

	size = mini.height_img * mini.width_img;
	i = 0;
	//c = 0;
	img = mini.img;
	ptr = mini.map;
	//printf("size == %d\n", size);
	while (i < size)
		mini.img[i++] = 0x0;
	//printf("i == %d\n", i);
	p_x = x / SIZE_CUBE * M_SIZE;
	p_y = y / SIZE_CUBE * M_SIZE;
	start[0] = p_x - mini.height_img / 2;
	start[1] = p_y - mini.width_img / 2;
	j = 0;
	//printf("pos x== %d et pos y == %d px == %d et py == %d\n", (int)x/SIZE_CUBE,(int)y/SIZE_CUBE,p_x,p_y);
	//printf("height == %d et width == %d\n", minimap.height_img, minimap.width_img);
	//printf("stat == %det stat == %d\n", start[0], start[1]);
	while (j < mini.height_img)
	{
		i = 0;
		while (i < mini.width_img)
		{
			if ((start[0] + (j) >= 0 && start[1] + (i) >= 0) && (start[0] + (j) < mini.height && start[1] + (i) < mini.width))
				img[j * mini.width_img + i] = ptr[(start[0] + j) * mini.width + (start[1] + i)];
			//else
			//	printf("ici? %d\n", c++);
			i++;
		}
		j++;
	}
	//printf("j == %d\n", j);
	//printf("i == %d\n", i);
}

void	set_circle_minimap(t_minimap mini)
{
	int	i;
	int	a;
	int	b;
	int	*ptr;
	int	x;
	int	y;
	
	a = mini.height_img / 2 - mini.radius;
	b = mini.width_img / 2 - mini.radius;
	i = 0;
	ptr = mini.img;
	x = 0;
	y = 0;
	while (x < mini.width_img)
	{
		b = mini.width_img / 2 - mini.radius;
		while (y < mini.height_img)
		{
			if ((((b - mini.radius) * (b - mini.radius)) + ((a - mini.radius) * (a - mini.radius))
				<= (mini.radius * mini.radius)))
				ptr[i] = ptr[i];
			else	
				ptr[i] = TRANSPARENT;
			i++;
			b++;
		}
		a++;
	}
}

void	init_circle(t_minimap mini)
{
	int	*ptr;
	int	i;
	int	x;
	int	y;

	y = 0;
	i = 0;
	ptr = mini.img;
	while (y < mini.height_img)
	{
		x = 0;
		while (x < mini.width_img)
		{
			if (!(((x - mini.radius) * (x - mini.radius)) + ((y - mini.radius) * (y - mini.radius))
				<= (mini.radius * mini.radius)))
				ptr[i] = TRANSPARENT;
			i++;
			x++;
		}
		y++;
	}
}

void	print_mini_player(int *ptr, double p_x, double p_y, t_minimap mini)
{
	p_y = (p_y / SIZE_CUBE) * M_SIZE;
	p_x = (p_x / SIZE_CUBE) * M_SIZE;
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
			if ((unsigned int)mini.img[i * mini.width_img + j] != TRANSPARENT)
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
	//set_circle_minimap(env->mini);
	init_circle(env->mini);
	print_mini_player(env->mini.img, env->map.pixel_y_player, env->map.pixel_x_player, env->mini);
	print_minimap(env->mini, env->mlx);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win, env->mlx.s_image, 0, 0);
}
