/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:41:34 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/30 01:29:52 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	handle_keypress(int key_code, t_env *env)
{
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
