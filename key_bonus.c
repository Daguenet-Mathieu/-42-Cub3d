/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:12:35 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/24 06:50:22 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	handle_key_util(int check_move, t_pos pos, t_env *env, int *move)
{
	if (check_move)
	{
		if (!check_collision(pos, *env) || BONUS == 0)
		{
			*move = do_move(&env->map.pixel_y_player, pos.new_y);
			*move = do_move(&env->map.pixel_x_player, pos.new_x);
		}
	}
}

void	display(int move, t_env *env, int player_axe)
{
	if (move || env->map.axe_player != player_axe)
	{
		set_map(env);
		get_next_wall(env);
		player_axe = env->map.axe_player;
	}
}

int	handle_key(t_env *env)
{
	t_pos		pos;
	int			move;
	int			check_move;
	static int	player_axe;

	move = 0;
	check_move = 0;
	if (env->key.space)
		env->map.gun.anim_state = ON_TOP;
	if (env->map.gun.anim_state == ON_TOP && check_time(env->map.gun.time_start, env->map.gun.interval) == 1)
	{
		move = 1;
		env->map.gun.time_start = ft_get_time();
		env->map.gun.curr_img++;
		if (env->map.gun.curr_img == 4)
		{
			env->map.gun.curr_img = 0;
			env->map.gun.anim_state = OFF;
		}
		env->map.gun.cur_img = env->map.gun.img[env->map.gun.curr_img];
	}
	ft_memset(&pos, 0, sizeof(t_pos));
	init_pos_t_d(&pos, env, &check_move);
	if (BONUS == 1)
		check_mouse(env);
	handle_key_util(check_move, pos, env, &move);
	ft_memset(&pos, 0, sizeof(t_pos));
	check_move = 0;
	init_pos_l_r(&pos, env, &check_move);
	handle_key_util(check_move, pos, env, &move);
	display(move, env, player_axe);
	return (0);
}
