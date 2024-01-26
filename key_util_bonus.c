/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_util_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:41:17 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/26 01:31:19 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	its_door(t_env env, int x, int y)
{
	int	i;

	i = 0;
	while (i < env.map.nb_door)
	{
		if (env.map.door1[i].x == x && env.map.door1[i].y == y)
			return (env.map.door1[i].anim_state);
		i++;
	}
	return (0);
}

int	check_collision(t_pos pos, t_env env)
{
	int	x;
	int	y;

	x = (int)(env.map.pixel_x_player + pos.new_x) / SIZE_CUBE;
	y = (int)(env.map.pixel_y_player + pos.new_y) / SIZE_CUBE;
	if (env.map.map[y][x] == '1')
		return (1);
	if (its_door(env, x, y))
		return (1);
	return (0);
}

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
