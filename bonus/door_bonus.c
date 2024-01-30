#include "cub3D_bonus.h"

double	calcul_distance_door(t_env *env, int *x, int *y)
{
	double	d_h;
	double	d_v;

	*y = -1;
	*x = -1;
	d_h = sqrt(pow((double)env->map.pixel_x_player - (double)env->h.x_door, 2) \
		+ pow((double)env->map.pixel_y_player - (double)env->h.y_door, 2));
	d_v = sqrt(pow((double)env->map.pixel_x_player - (double)env->v.x_door, 2) \
		+ pow((double)env->map.pixel_y_player - (double)env->v.y_door, 2));
	if (d_h <= d_v)
	{
		env->map.grid_x_door = env->h.grid_x_door;
		env->map.grid_y_door = env->h.grid_y_door;
		*y = env->h.y_door;
		return (d_h);
	}
	else
	{
		env->map.grid_x_door = env->v.grid_x_door;
		env->map.grid_y_door = env->v.grid_y_door;
		*x = env->v.x_door;
		return (d_v);
	}
}

void	calcul_door(t_env *env, t_get_next_wall *s)
{
	env->map.distance_door = \
	calcul_distance_door(env, &s->x_door, &s->y_door);
	remove_fishbowl(&env->map.distance_door, s->i);
	s->height_door = \
	(SIZE_CUBE / env->map.distance_door) * env->map.projection_plane;
}

void	init_value_door(t_print_wall *s, t_get_next_wall *w, t_env *e, int *st)
{
	int	tmp;

	*st = its_door(*e, e->map.grid_x_door, e->map.grid_y_door);
	tmp = w->height_door;
	w->height_door = tmp * *st / 100;
	s->height_draw = w->height_door;
	if (s->height_draw > HEIGHT_PLANE)
	{
		s->height_draw = HEIGHT_PLANE;
		s->diff = w->height_door - s->height_draw;
	}
	s->y_start = (HEIGHT_PLANE / 2) - \
	((s->height_draw - (tmp - w->height_door)) / 2);
}

void	init_print_door(t_print_wall *s, t_env *env, t_get_next_wall w, int st)
{
	int	ratio;

	ratio = env->map.door.height * st / 100;
	if (w.x_door > -1)
		s->index_wall = fmod(env->v.y_door, SIZE_CUBE);
	else if (w.y_door > -1)
		s->index_wall = fmod(env->h.x_door, SIZE_CUBE);
	s->orientation = DOOR;
	env->map.img = env->map.door.img;
	env->map.size_line = env->map.door.size_line;
	env->map.height = env->map.door.height;
	s->ratio_leon = ratio / w.height_door;
	s->column_t = s->index_wall * env->map.door.size_line / SIZE_CUBE;
	s->diff /=  w.height_door / ratio * 2;
}
