/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:41:34 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/28 17:52:42 by madaguen         ###   ########.fr       */
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
	if (key_code == 65361)
		ajust_key_release(&env->key.arrow_right, &env->key.arrow_left);
	if (key_code == 65363)
		ajust_key_release(&env->key.arrow_left, &env->key.arrow_right);
	if (key_code == 100)
		ajust_key_release(&env->key.right, &env->key.left);
	else if (key_code == 119)
		ajust_key_release(&env->key.up, &env->key.down);
	else if (key_code == 97)
		ajust_key_release(&env->key.left, &env->key.right);
	else if (key_code == 115)
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

void	set_anime_state_door(t_door *door, int size, int x, int y)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (door[i].x == x && door[i].y == y)
		{
			printf("ici???? openinig == %d\n", door[i].is_openning);
			if (door[i].is_openning == CLOSE || door[i].is_openning == ON_DOWN)
				door[i].is_openning = ON_TOP;
			else if (door[i].is_openning == OPEN || door[i].is_openning == ON_TOP)
				door[i].is_openning = ON_DOWN;
			printf("ici???? openinig == %d\n", door[i].is_openning);
		}
		i++;
	}	
}

void	do_door(t_env *env)
{
	const int	x = (int)env->map.pixel_x_player / SIZE_CUBE;
	const int	y = (int)env->map.pixel_y_player / SIZE_CUBE;

	if (env->map.map[y][x + 1] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door, x + 1, y);
	if (env->map.map[y + 1][x] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door, x, y + 1);
	if (env->map.map[y + 1][x + 1] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door,x + 1, y + 1);
	if (env->map.map[y - 1][x] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door, x, y - 1);
	if (env->map.map[y][x - 1] == 'd')
		set_anime_state_door(env->map.door1, env->map.nb_door, x - 1, y);
	if (env->map.map[y - 1][x - 1] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door, x - 1, y - 1);
	if (env->map.map[y + 1][x - 1] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door, x - 1, y + 1);
	if (env->map.map[y - 1][x + 1] == 'd')
	 	set_anime_state_door(env->map.door1, env->map.nb_door, x + 1, y - 1);
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
