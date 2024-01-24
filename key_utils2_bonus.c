/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:41:34 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/24 07:19:48 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (key_code == 32)
		env->key.space = 0;
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

void	set_anime_state_door(t_map *map)
{
	(void) map;
	//door 1 et 2 inverser le state on up down si le 2 a 0 set en fct de OPEN ou CLOSE
}

void	do_door(t_env *env)
{
	if (env->map.map[(int)env->map.pixel_y_player][(int)env->map.pixel_x_player + 1] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player + 1][(int)env->map.pixel_x_player] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player + 1][(int)env->map.pixel_x_player + 1] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player - 1][(int)env->map.pixel_x_player] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player - 1][(int)env->map.pixel_x_player - 1] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player][(int)env->map.pixel_x_player - 1] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player + 1][(int)env->map.pixel_x_player - 1] == 'D')
		set_anime_state_door(&env->map);
	if (env->map.map[(int)env->map.pixel_y_player - 1][(int)env->map.pixel_x_player + 1] == 'D')
		set_anime_state_door(&env->map); 
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
