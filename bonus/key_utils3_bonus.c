/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:10:38 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/31 00:40:58 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	display(int move, t_env *env, int player_axe)
{
	if (move || env->map.axe_player != player_axe)
	{
		ft_memcpy(env->mlx.image, env->map.cpy_c_f, \
		(WIDTH * HEIGHT_PLANE) * sizeof(int));
		get_next_wall(env);
		player_axe = env->map.axe_player;
	}
}

int	handle_keypress(int key_code, t_env *env)
{
	if (key_code == 114)
		do_door(env);
	if (key_code == 32)
		env->key.space = 1;
	if (key_code == 65307)
		return (write(1, "\n", 1), free_struct(env), 0);
	if (key_code == 65361)
		ajust_key_press(&env->key.arrow_right, &env->key.arrow_left);
	if (key_code == 65363)
		ajust_key_press(&env->key.arrow_left, &env->key.arrow_right);
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

int	do_move(double *player, double new_pos)
{
	*player += new_pos;
	return (1);
}
