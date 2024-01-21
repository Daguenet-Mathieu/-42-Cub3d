/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:18:22 by auferran          #+#    #+#             */
/*   Updated: 2024/01/21 19:10:16 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	printmap(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
}

void	set_map(t_env *env)
{
	int	y;
	int	i;

	y = 0;
	while (y < ((HEIGHT_PLANE) / 2))
	{
		i = 0;
		while (i < (WIDTH))
		{
			env->mlx.image[(y * WIDTH) + i] = env->map.ceiling;
			i++;
		}
		y++;
	}
	while (y < ((HEIGHT_PLANE)))
	{
		i = 0;
		while (i < (WIDTH))
		{
			env->mlx.image[(y * WIDTH) + i] = env->map.floor;
			i++;
		}
		y++;
	}
}

int	init_win(t_env *env)
{
	env->mlx.mlx = mlx_init();
	if (!env->mlx.mlx)
		return (write(2, "MLX FAILURE\n", 13));
	env->mlx.mlx_win = mlx_new_window(env->mlx.mlx, WIDTH, HEIGHT_PLANE, \
	"cub3D");
	if (!env->mlx.mlx_win)
		return (write(2, "WINDOW FAILURE\n", 16));
	env->mlx.s_image = mlx_new_image(env->mlx.mlx, WIDTH, HEIGHT_PLANE);
	if (!env->mlx.s_image)
		return (write(2, "IMAGE FAILURE\n", 15));
	env->mlx.image = (int *)mlx_get_data_addr \
	(env->mlx.s_image, &env->mlx.bpp, &env->mlx.size_line, &env->mlx.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	if (argc != 2)
		return (write(2, "Incorrect number of arguments\n", 31));
	if (!get_map(&env.map, argv[1]))
		return (1);
	get_pos_player(&env.map);
	init_mp_info(&env.map);
	if (!create_minimap(&env.mini, env.map.map))
		return (free_struct(&env), 0);
	if (init_win(&env))
		return (1);
	set_hooks_mlx(&env);
	mlx_loop(env.mlx.mlx);
	return (0);
}
