/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:54:03 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/26 04:20:27 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_print_value_x(t_print_wall *s, t_env *env, t_get_next_wall wall)
{
	s->index_wall = fmod(env->v.new_y, SIZE_CUBE);
	if ((int)env->map.pixel_x_player > wall.x)
	{
		s->orientation = WEST;
		env->map.img = env->map.t_we.img;
		s->ratio_leon = env->map.t_we.height / wall.height;
		s->column_t = s->index_wall * \
			(double)env->map.t_we.height / (double)SIZE_CUBE;
		s->diff /= wall.height / env->map.t_we.height * 2;
	}
	else
	{
		s->orientation = EAST;
		env->map.img = env->map.t_ea.img;
		s->ratio_leon = env->map.t_ea.height / wall.height;
		s->column_t = s->index_wall * \
			(double)env->map.t_ea.height / (double)SIZE_CUBE;
		s->diff /= wall.height / env->map.t_ea.height * 2;
	}
}

void	init_print_value_y(t_print_wall *s, t_env *env, t_get_next_wall wall)
{
	s->index_wall = fmod(env->h.new_x, SIZE_CUBE);
	if ((int)env->map.pixel_y_player > wall.y)
	{
		s->orientation = NORTH;
		env->map.img = env->map.t_no.img;
		s->ratio_leon = env->map.t_no.height / wall.height;
		s->column_t = s->index_wall * \
			(double)env->map.t_no.height / (double)SIZE_CUBE;
		s->diff /= wall.height / env->map.t_no.height * 2;
	}
	else
	{
		s->orientation = SOUTH;
		env->map.img = env->map.t_so.img;
		s->ratio_leon = env->map.t_so.height / wall.height;
		s->column_t = s->index_wall * \
			(double)env->map.t_so.height / (double)SIZE_CUBE;
		s->diff /= wall.height / env->map.t_so.height * 2;
	}
}

int	get_pixel(t_env *env, t_print_wall s, int size_line)
{
	double	j;
	double	tmp;
	double	pixel;
	int		pixel_color;
	int		red;
	int		green;
	int		blue;
	int		new_color;

	j = s.diff * size_line;
	j += s.i * size_line * s.ratio_leon;
	tmp = (int)j % size_line;
	j -= tmp;
	pixel = j + s.column_t;
	pixel_color = env->map.img[(int)pixel];
	if (env->map.distance_wall > 150)
	{
		get_rgb(pixel_color, &red, &green, &blue);
		new_color = get_shading_wall(red, green, blue, env->map.distance_wall);
	}
	else
		new_color = pixel_color;
	return (new_color);
}

void	draw_pixel_door(t_print_wall *s, t_env *env, int i_rayon, t_get_next_wall wall)
{
	int	y_start;
	int	state;
	int ratio;
	int	axe;

	state = its_door(*env, env->h.grid_x_door, env->h.grid_y_door);
	ratio = (s->height_draw_door * state) / 100;
	y_start = (HEIGHT_PLANE / 2) - (s->height_draw_door / 2);

	if (wall.x_door > -1)
		axe = env->v.y_door;
	else
		axe = env->h.x_door;
	s->index_wall = fmod(axe, SIZE_CUBE);
	env->map.img = env->map.door.img;
	s->ratio_leon = env->map.door.height / wall.height_door;
	s->column_t = s->index_wall * \
	(double)env->map.door.height / (double)SIZE_CUBE;
	s->diff_door /=  wall.height_door / env->map.door.height * 2;
	
	while (s->i < (int)s->height_draw_door)
	{
		env->mlx.image[((y_start + s->i) * WIDTH) + i_rayon] = \
			get_pixel(env, *s, env->map.door.size_line);
		s->i++;
	}
	env->map.door_here = 0;
}

void	draw_pixel(t_print_wall s, t_env *env, int i_rayon)
{

	while (s.i < (int)s.height_draw)
	{
		if (s.orientation == NORTH)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_no.size_line);
		else if (s.orientation == SOUTH)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_so.size_line);
		else if (s.orientation == EAST)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_ea.size_line);
		else if (s.orientation == WEST)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_we.size_line);
		s.i++;
	}
}

void	print_wall(t_env *env, t_get_next_wall wall)
{
	t_print_wall	s;

	ft_memset(&s, 0, sizeof(t_print_wall));
	s.height_draw = wall.height;
	if (s.height_draw > HEIGHT_PLANE)
	{
		s.height_draw = HEIGHT_PLANE;
		s.diff = (wall.height - s.height_draw);
	}
	s.height_draw_door = wall.height_door;
	if (s.height_draw_door > HEIGHT_PLANE)
	{
		s.height_draw_door = HEIGHT_PLANE;
		s.diff_door = (wall.height_door - s.height_draw_door);
	}
	if (wall.x > -1)
		init_print_value_x(&s, env, wall);
	else if (wall.y > -1)
		init_print_value_y(&s, env, wall);
	s.y_start = (HEIGHT_PLANE / 2) - (s.height_draw / 2);
	draw_pixel(s, env, wall.i_rayon);
	if (env->map.door_here == 1)
		draw_pixel_door(&s, env, wall.i_rayon, wall);
}
