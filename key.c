#include "cub3D.h"

int	do_move(double *player, double new_pos)
{
	*player += new_pos;
	return (1);
}

double	calcul_angle_l_r(double axe_player, int nb)
{
	double	angle;

	if (nb == 1)
		angle = axe_player - 90;
	if (nb == 2)
		angle = axe_player + 90;
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

void	init_pos_l_r(t_pos *pos, t_env *env, int *move)
{
	double	angle;
	double	y_displacement;
	double	x_displacement;

	if (env->key.right)
	{
		angle = calcul_angle_l_r(env->map.axe_player, 1);
		angle = (angle * M_PI) / 180;
		y_displacement = sin(angle) * SPEED;
		x_displacement = cos(angle) * SPEED;
		pos->new_x += x_displacement;
		pos->new_y -= y_displacement;
		*move += 1;
	}
	if (env->key.left)
	{
		angle = calcul_angle_l_r(env->map.axe_player, 2);
		angle = (angle * M_PI) / 180;
		y_displacement = sin(angle) * SPEED;
		x_displacement = cos(angle) * SPEED;
		pos->new_x += x_displacement;
		pos->new_y -= y_displacement;
		*move += 1;
	}
}

void	init_pos_t_d(t_pos *pos, t_env *env, int *move)
{
	double	angle;
	double	y_displacement;
	double	x_displacement;

	angle = (env->map.axe_player * M_PI) / 180;
	y_displacement = sin(angle) * SPEED;
	x_displacement = cos(angle) * SPEED;
	if (env->key.down)
	{
		pos->new_x -= x_displacement;
		pos->new_y += y_displacement;
		*move += 1;
	}
	if (env->key.up)
	{
		pos->new_x += x_displacement;
		pos->new_y -= y_displacement;
		*move += 1;
	}
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
	if (key_code == 65361)
		env->map.axe_player += SPEED_2;
	if (key_code == 65363)
		env->map.axe_player -= SPEED_2;
	if (env->map.axe_player < 0)
		env->map.axe_player = 359;
	if (env->map.axe_player > 360)
		env->map.axe_player = 0;
	if (key_code == 100)
		ajust_key_press(&env->key.right, &env->key.left);
	else if (key_code == 119)
		ajust_key_press(&env->key.up, &env->key.down);
	else if (key_code == 97)
		ajust_key_press(&env->key.left, &env->key.right);
	else if (key_code == 115)
		ajust_key_press(&env->key.down, &env->key.up);
	return (key_code);
}

int	handle_key(t_env *env)
{
	t_pos		pos;
	int			move;
	int			check_move;
	static int player_axe;

	move = 0;
	check_move = 0;
	ft_memset(&pos, 0, sizeof(t_pos));
	init_pos_t_d(&pos, env, &check_move);
	if (check_move)
	{
		move = do_move(&env->map.pixel_y_player, pos.new_y);
		move = do_move(&env->map.pixel_x_player, pos.new_x);
	}
	ft_memset(&pos, 0, sizeof(t_pos));
	check_move = 0;
	init_pos_l_r(&pos, env, &check_move);
	if (check_move)
	{
		move = do_move(&env->map.pixel_y_player, pos.new_y);
		move = do_move(&env->map.pixel_x_player, pos.new_x);
	}
	if (move || env->map.axe_player != player_axe)
	{
		set_map(env);
		get_next_wall(env);
		player_axe = env->map.axe_player;
	}
	return (0);
}
