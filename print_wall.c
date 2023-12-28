#include "cub3D.h"

int	get_pixel(t_env *env, t_print_wall s, int size_line)
{
	double	j;
	double	tmp;
	double	pixel;

	j = s.diff * size_line;
	j += s.i * size_line * s.ratio_leon;
	tmp = (int)j % size_line;
	j -= tmp;
	pixel = j + s.column_texture;
	return (env->map.img[(int)pixel]);
}

void	init_orientation_indexwall(t_print_wall *s, t_env *env, int x, int y)
{
	if (x > -1)
	{
		if ((int)env->map.pixel_x_player > x)
			s->orientation = WEST;
		else
			s->orientation = EAST;
		s->index_wall = fmod(env->v.new_y, SIZE_CUBE);
	}
	if (y > -1)
	{
		if ((int)env->map.pixel_y_player > y)
			s->orientation = NORTH;
		else
			s->orientation = SOUTH;
		s->index_wall = fmod(env->h.new_x, SIZE_CUBE);
	}
}

void	draw_pixel(t_print_wall s, t_env *env, int i_rayon)
{
	while (s.i < (int)s.height_draw)
	{
		if (s.orientation == NORTH)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] =
				get_pixel(env, s, env->map.texture_no.size_line);
		else if (s.orientation == SOUTH)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] =
				get_pixel(env, s, env->map.texture_no.size_line);
		else if (s.orientation == EAST)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] =
				get_pixel(env, s, env->map.texture_no.size_line);
		else if (s.orientation == WEST)
			env->mlx.image[((s.y_start + s.i) * WIDTH) + i_rayon] =
				get_pixel(env, s, env->map.texture_no.size_line);
		s.i++;
	}
}

void	print_wall(t_env *env, t_get_next_wall wall)
{
	t_print_wall	s;

	ft_memset(&s, 0, sizeof(t_print_wall));
	env->map.img = env->map.texture_no.img;
	init_orientation_indexwall(&s, env, wall.x, wall.y);
	s.i = 0;
	s.ratio_leon = env->map.texture_no.height / wall.height;
	s.column_texture = s.index_wall * (double)env->map.texture_no.height / (double)SIZE_CUBE;
	s.height_draw = wall.height;
	if (s.height_draw > HEIGHT_PLANE)
	{
		s.height_draw = HEIGHT_PLANE;
		s.diff = (wall.height - s.height_draw) / (wall.height / s.height_draw * 2);
	}
	s.y_start = (HEIGHT_PLANE / 2) - (s.height_draw / 2);
	draw_pixel(s, env, wall.i_rayon);
}
