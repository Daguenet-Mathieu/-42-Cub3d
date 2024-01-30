/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:05:22 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/30 02:56:37 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_weapon(t_env *env)
{
	const t_image	*i = env->map.gun.img;

	init_sprite(env, "img/weapon/gun/1.xpm", &env->map.gun.img[0]);
	if (!i[0].ptr)
		return (0);
	env->map.gun.img[0].img = get_data((t_image *)&env->map.gun.img[0]);
	env->map.gun.img[0].size_line /= sizeof(int);
	if ((int)W_SIZE)
	{
		if (!zoom_img((t_image *)&i[0], W_SIZE))
			return (0);
	}
	env->map.gun.cur_img = env->map.gun.img[0];
	return (1);
}

int	init_img(t_env *env)
{
	env->map.t_no.ptr = mlx_xpm_file_to_image(env->mlx.mlx, \
	env->map.no, &env->map.t_no.size_line, &env->map.t_no.height);
	env->map.t_so.ptr = mlx_xpm_file_to_image(env->mlx.mlx, \
	env->map.so, &env->map.t_so.size_line, &env->map.t_so.height);
	env->map.t_we.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.we, \
	&env->map.t_we.size_line, &env->map.t_we.height);
	env->map.t_ea.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.ea, \
	&env->map.t_ea.size_line, &env->map.t_ea.height);
	if (!env->map.t_no.ptr || !env->map.t_so.ptr || \
	!env->map.t_ea.ptr || !env->map.t_we.ptr)
		return (0);
	env->map.t_no.img = (int *)mlx_get_data_addr(env->map.t_no.ptr, \
	&env->map.t_no.bpp, &env->map.t_no.size_line, &env->map.t_no.endian);
	env->map.t_so.img = (int *)mlx_get_data_addr(env->map.t_so.ptr, \
	&env->map.t_so.bpp, &env->map.t_so.size_line, &env->map.t_so.endian);
	env->map.t_we.img = (int *)mlx_get_data_addr(env->map.t_we.ptr, \
	&env->map.t_we.bpp, &env->map.t_we.size_line, &env->map.t_we.endian);
	env->map.t_ea.img = (int *)mlx_get_data_addr(env->map.t_ea.ptr, \
	&env->map.t_ea.bpp, &env->map.t_ea.size_line, &env->map.t_ea.endian);
	return (1);
}

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
	if (!init_img(env) || !get_weapon(env))
		return (write(2, "fail to load img\n", 18), 0);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	env->map.t_no.size_line /= 4;
	env->map.t_so.size_line /= 4;
	env->map.t_we.size_line /= 4;
	env->map.t_ea.size_line /= 4;
	if (!init_shading_map(env))
		return (0);
	return (1);
}
