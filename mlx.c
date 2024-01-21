/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:05:22 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/21 22:47:54 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
}

void	free_struct(t_env *env)
{
	if (env->mlx.image)
		mlx_destroy_image(env->mlx.mlx, env->mlx.s_image);
	if (env->mlx.mlx_win)
		mlx_destroy_window(env->mlx.mlx, env->mlx.mlx_win);
	if (env->mlx.mlx)
		mlx_destroy_display(env->mlx.mlx);
	if (env->mlx.mlx)
		mlx_loop_end(env->mlx.mlx);
	free(env->mlx.mlx);
	free_tab(env->map.map);
	exit(0);
}

int	mlx_close(t_env *env)
{
	write(1, "\n", 1);
	free_struct(env);
	return (0);
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

int	set_hooks_mlx(t_env *env)
{
	if (!init_img(env))
		return (0);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	if (BONUS == 1)
		mlx_mouse_hide(env->mlx.mlx, env->mlx.mlx_win);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	env->map.t_no.size_line /= 4;
	env->map.t_so.size_line /= 4;
	env->map.t_we.size_line /= 4;
	env->map.t_ea.size_line /= 4;
	return (1);
}
