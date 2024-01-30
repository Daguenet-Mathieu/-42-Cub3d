/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 02:56:50 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/30 02:59:03 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	destroy_gun(t_env *env, t_gun gun)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (gun.img[i].ptr)
			mlx_destroy_image(env->mlx.mlx, gun.img[i].ptr);
		if (gun.img[i].new_img)
			free(gun.img[i].new_img);
		i++;
	}
}

void	free_struct_util(t_env *env)
{
	if (env->mini.img)
		free (env->mini.img);
	if (env->mini.map)
		free (env->mini.map);
	if (env->map.no)
		free(env->map.no);
	if (env->map.so)
		free(env->map.so);
	if (env->map.we)
		free(env->map.we);
	if (env->map.ea)
		free(env->map.ea);
	if (env->map.cpy_c_f)
		free(env->map.cpy_c_f);
}

void	free_struct(t_env *env)
{
	free_struct_util(env);
	if (env->map.door.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.door.ptr);
	if (env->map.door1)
		free (env->map.door1);
	destroy_gun(env, env->map.gun);
	if (env->mlx.s_image)
		mlx_destroy_image(env->mlx.mlx, env->mlx.s_image);
	if (env->map.t_no.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_no.ptr);
	if (env->map.t_so.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_so.ptr);
	if (env->map.t_we.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_we.ptr);
	if (env->map.t_ea.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_ea.ptr);
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
