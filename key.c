#include "cub3D.h"


int	do_move(double *player, double new_pos)
{
	*player = new_pos;
	return (1);
}

void	init_pos_l_r(t_pos *pos, t_env *env, int *move)
{
	pos->x = env->map.pixel_x_player;
	pos->y = env->map.pixel_y_player;
	pos->new_x = pos->x;
	pos->new_y = pos->y;
	if (env->key.right)
	{
		pos->new_x += SPEED;
		*move = *move + 1;
	}
	if (env->key.left)
	{
		pos->new_x -= SPEED;
		*move = *move + 1;
	}
	if (pos->new_x <= 0)
		pos->new_x = env->map.x_max - 1;
	else if (pos->new_x <= env->map.x_max)
		pos->new_x = 1;
}

void	init_pos_t_d(t_pos *pos, t_env *env, int *move)
{
	pos->x = env->map.pixel_x_player;
	pos->y = env->map.pixel_y_player;
	pos->new_x = pos->x;
	pos->new_y = pos->y;
	if (env->key.down)
	{
		pos->new_y = pos->y + SPEED;
		*move = *move + 1;
	}
	if (env->key.up)
	{
		pos->new_y = pos->y - SPEED;
		*move = *move + 1;
	}
	if (pos->new_y >= env->map.y_max)
		pos->new_y = 1;
	else if (pos->new_y <= 0)
		pos->new_y = env->map.y_max - 1;
}

void	ajust_key_release(int *key1, int *key2)
{
	if (*key1 == 2)
	*key2 = 1;
	else if (*key2 == 2)
		*key2 = 1;
	*key1 = 0;
}

int	handle_keyrelease(int key_code, t_env *env)
{
	printf ("keucode == %d\n", key_code);
	if (key_code == 65363 || key_code == 100)
		ajust_key_release(&env->key.right, &env->key.left);
	else if (key_code == 65362 || key_code == 119)
		ajust_key_release(&env->key.up, &env->key.down);
	else if (key_code == 65361 || key_code == 97)
		ajust_key_release(&env->key.left, &env->key.right);
	else if (key_code == 65364 || key_code == 115)
		ajust_key_release(&env->key.down, &env->key.up);
	return (key_code);
}

void	ajust_key_press(int *key1, int *key2)
{
	if (*key2)
		*key1 = 2;
	else
		*key1 = 1;
	*key2 = 0;
}

int	handle_keypress(int key_code, t_env *env)
{
	if (key_code == 65307)
		return (write(1, "\n", 1), free_struct(env), 0);
//	if (key_code == 101)
//	{
//		env->minimap.active = env->minimap.active ^ 1;
//		load_map(env);
//	}
	printf ("keucode == %d", key_code);
	if (key_code == 65361)
		env->map.axe_player -= 1;
	if (key_code == 65363)
		env->map.axe_player += 1;
	if (env->map.axe_player == -1)
		env->map.axe_player = 359;
	if (env->map.axe_player == 360)
		env->map.axe_player = 0;
	if (key_code == 100)
		ajust_key_press(&env->key.right, &env->key.left);
	else if (key_code == 119)
		ajust_key_press(&env->key.up, &env->key.down);
	else if (key_code == 97)
		ajust_key_press(&env->key.left, &env->key.right);
	else if (key_code == 115)
		ajust_key_press(&env->key.down, &env->key.up);
	printf ("down == %d, up == %d\n", env->key.down, env->key.up);
	return (key_code);
}

int	handle_key(t_env *env)
{
	t_pos	pos;
	int		move;
	int		check_move;
	static int player_axe;
	//static int i;
	move = 0;
	check_move = 0;
	init_pos_t_d(&pos, env, &check_move);
	if (check_move)
		move = do_move(&env->map.pixel_y_player, pos.new_y);
	check_move = 0;
	init_pos_l_r(&pos, env, &check_move);
	if (check_move)
		move = do_move(&env->map.pixel_x_player, pos.new_x);
	if (move || env->map.axe_player != player_axe)
	{
		//printf("i == %d player x == %f, player y == %f\n", i++, env->map.pixel_x_player, env->map.pixel_y_player);
		set_map(env);
		get_next_wall(env);
		player_axe = env->map.axe_player;
		printf("player_axe == %d\n", player_axe);
	}
	return (0);
}