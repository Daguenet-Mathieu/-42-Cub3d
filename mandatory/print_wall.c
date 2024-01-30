/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:54:03 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/30 02:17:34 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_print_value_x(t_print_wall *s, t_env *env, t_get_next_wall wall)
{
	s->index_wall = fmod(env->v.new_y, SIZE_CUBE);
	if ((int)env->map.pixel_x_player > wall.x)
	{
		s->orientation = WEST;
		env->map.img = env->map.t_we.img;
		env->map.size_line = env->map.t_we.size_line;
		env->map.height = env->map.t_we.height;
		s->ratio_leon = env->map.t_we.height / wall.height;
		s->column_t = s->index_wall * env->map.t_we.size_line/ SIZE_CUBE;
		s->diff /= wall.height / env->map.t_we.height * 2;
	}
	else
	{
		s->orientation = EAST;
		env->map.img = env->map.t_ea.img;
		env->map.size_line = env->map.t_ea.size_line;
		env->map.height = env->map.t_ea.height;
		s->ratio_leon = env->map.t_ea.height / wall.height;
		s->column_t = s->index_wall * env->map.t_ea.size_line / SIZE_CUBE;
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
		env->map.size_line = env->map.t_no.size_line;
		env->map.height = env->map.t_no.height;
		s->ratio_leon = env->map.t_no.height / wall.height;
		s->column_t = s->index_wall * env->map.t_no.size_line / SIZE_CUBE;
		s->diff /= wall.height / env->map.t_no.height * 2;
	}
	else
	{
		s->orientation = SOUTH;
		env->map.img = env->map.t_so.img;
		env->map.size_line = env->map.t_so.size_line;
		env->map.height = env->map.t_so.height;
		s->ratio_leon = env->map.t_so.height / wall.height;
		s->column_t = s->index_wall * env->map.t_so.size_line / SIZE_CUBE;
		s->diff /= wall.height / env->map.t_so.height * 2;
	}
}

int	get_pixel(t_env *env, t_print_wall s, int size_line, int nb)
{
	double	j;
	double	pixel;
	int		pixel_color;
	int		red;
	int		green;
	int		blue;

	j = s.diff * size_line;
	j += s.i * size_line * s.ratio_leon;
	j -= (int)j % size_line;
	pixel = j + s.column_t;
	if (pixel > (env->map.size_line * env->map.height) || pixel < 0)
		return (0);
	pixel_color = env->map.img[(int)pixel];
	if (nb == 1)
		env->map.distance_wall = env->map.distance_door;
	if (env->map.distance_wall > 150)
	{
		get_rgb(pixel_color, &red, &green, &blue);
		pixel_color = get_shading_wall(red, green, blue, env->map.distance_wall);
	}
	return (pixel_color);
}

void	init_print_value_door(t_print_wall *s, t_env *env, t_get_next_wall wall, int state)
{
	int	ratio;

	ratio = env->map.door.height * state / 100;
	if (wall.x_door > -1)
		s->index_wall = fmod(env->v.y_door, SIZE_CUBE);
	else if (wall.y_door > -1)
		s->index_wall = fmod(env->h.x_door, SIZE_CUBE);
	s->orientation = DOOR;
	env->map.img = env->map.door.img;
	env->map.size_line = env->map.door.size_line;
	env->map.height = env->map.door.height;
	s->ratio_leon = ratio / wall.height_door;
	s->column_t = s->index_wall * env->map.door.size_line / SIZE_CUBE;
	s->diff /=  wall.height_door / ratio * 2;
}

void	draw_pixel(t_print_wall s, t_env *env, int i_rayon)
{
	while (s.i < (int)s.height_draw)
	{
		if (((s.y_start + s.i) * WIDTH) + i_rayon > (HEIGHT_PLANE * WIDTH))
			return ;
		if (s.orientation == NORTH)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_no.size_line, 0);
		else if (s.orientation == SOUTH)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_so.size_line, 0);
		else if (s.orientation == EAST)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_ea.size_line, 0);
		else if (s.orientation == WEST)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.t_we.size_line, 0);
		else if (s.orientation == DOOR)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] = \
				get_pixel(env, s, env->map.door.size_line, 1);
		s.i++;
	}
}

void	print_wall(t_env *env, t_get_next_wall *wall)
{
	t_print_wall	s;
	const int		state = 0;
	int				tmp;

	ft_memset(&s, 0, sizeof(t_print_wall));
	s.height_draw = wall->height;
	if (s.height_draw > HEIGHT_PLANE)
	{
		s.height_draw = HEIGHT_PLANE;
		s.diff = wall->height - s.height_draw;
	}
	if (wall->x > -1)
		init_print_value_x(&s, env, *wall);
	else if (wall->y > -1)
		init_print_value_y(&s, env, *wall);
	s.y_start = (HEIGHT_PLANE / 2) - (s.height_draw / 2);
	draw_pixel(s, env, wall->i_rayon);
	if ((env->v.door_here == 1 || env->h.door_here == 1) && env->map.distance_door < env->map.distance_wall)
	{
		tmp = wall->height_door;
		wall->height_door = tmp * state / 100;
		s.height_draw = wall->height_door;
		if (s.height_draw > HEIGHT_PLANE)
		{
			s.height_draw = HEIGHT_PLANE;
			s.diff = wall->height_door - s.height_draw;
		}
		s.y_start = (HEIGHT_PLANE / 2) - ((s.height_draw - (tmp - wall->height_door)) / 2);
		init_print_value_door(&s, env, *wall, state);
		draw_pixel(s, env, wall->i_rayon);
	}
}
