/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:18:22 by auferran          #+#    #+#             */
/*   Updated: 2024/01/25 20:03:18 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	set_map(t_env *env, int *ptr)
{
	int	y;
	int	i;
	int	x;
	int	color;

	y = 0;
	while (y < ((HEIGHT_PLANE) / 2))
	{
		i = 0;
		color = c_f_shading(env->map.ceiling, y);
		while (i < (WIDTH))
		{
			ptr[(y * WIDTH) + i] = color;
			i++;
		}
		y++;
	}
	x = 0;
	y = HEIGHT_PLANE - 1;
	while (y >= ((HEIGHT_PLANE / 2)))
	{
		i = 0;
		color = c_f_shading(env->map.floor, x);
		while (i < (WIDTH))
		{
			ptr[(y * WIDTH) + i] = color;
			i++;
		}
		x++;
		y--;
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

int	check_char(char **map)
{
	int	player;
	int	i;
	int	j;

	j = 0;
	player = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (its_player(map[j][i]))
				player++;
			else if (map[j][i] != '1' && map[j][i] != '0' && \
			!ft_isspace(map[j][i]))
				return (write(2, "invalid char in map\n", 21), 0);
			i++;
		}
		j++;
	}
	if (player > 1 || player == 0)
		return (write(2, "only one player required\n", 26), 0);
	return (1);
}

int	check_char_bonus(char **map)
{
	int	player;
	int	i;
	int	j;

	j = 0;
	player = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (its_player(map[j][i]))
				player++;
			else if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != 'D' \
			&& !ft_isspace(map[j][i]))
				return (write(2, "invalid char in map\n", 21), 0);
			i++;
		}
		j++;
	}
	if (player > 1 || player == 0)
		return (write(2, "only one player required\n", 26), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	if (argc != 2)
		return (write(2, "Incorrect number of arguments\n", 31));
	if (!get_map(&env.map, argv[1]))
		return (1);
	if (!check_char(env.map.map))
		return (1);
	get_pos_player(&env.map);
	if (!check_map(&env.map))
		return (1);
	init_mp_info(&env.map);
	if (!create_minimap(&env.mini, env.map.map))
		return (free_struct(&env), 0);
	if (init_win(&env))
		return (1);
	if (!set_hooks_mlx(&env))
		return (1);
	env.map.gun.time_start = ft_get_time();
	env.map.gun.interval = GUN_TIME / 4;
	env.map.door1.time_start = ft_get_time();
	env.map.door2.time_start = ft_get_time();
	env.map.door1.interval = DOOR_TIME / 100;
	env.map.door2.interval = DOOR_TIME / 100;
	mlx_loop(env.mlx.mlx);
	return (0);
}
