/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:05:22 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/31 00:01:42 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	init_shading_map(t_env *env)
{
	env->map.cpy_c_f = malloc(sizeof(int) * (WIDTH * HEIGHT_PLANE));
	if (!env->map.cpy_c_f)
		return (0);
	set_map(env, env->map.cpy_c_f);
	return (1);
}

int	set_hooks_mlx(t_env *env)
{
	if (!init_img(env) || !get_door(env) || !get_weapon(env))
		return (write(2, "fail to load img\n", 18), 0);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	if (LEAK == 1)
		mlx_mouse_hide(env->mlx.mlx, env->mlx.mlx_win);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	env->map.t_no.size_line /= 4;
	env->map.t_so.size_line /= 4;
	env->map.t_we.size_line /= 4;
	env->map.t_ea.size_line /= 4;
	if (!init_shading_map(env))
		return (0);
	return (1);
}
