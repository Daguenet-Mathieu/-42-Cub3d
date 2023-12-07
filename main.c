/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:18:22 by auferran          #+#    #+#             */
/*   Updated: 2023/12/05 18:54:11 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*void	printmap(char **map)
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
}*/

int	main(int argc, char **argv)
{
	int		bpp;
	int		endian;
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	if (argc != 2)
		return (write(2, "Incorrect number of arguments\n", 31));
	if (!get_map(&env.map, argv[1]))
		return (1);
	get_pos_player(&env.map);
	get_next_wall(&env);
	env.mlx.mlx = mlx_init();
	if (!env.mlx.mlx)
		return (write(2, "MLX FAILURE\n", 13));
	env.mlx.mlx_win = mlx_new_window(env.mlx.mlx, WIDTH, HEIGHT_PLANE, "cub3D");
	if (!env.mlx.mlx_win)
		return (write(2, "WINDOW FAILURE\n", 16));
	env.mlx.s_image = mlx_new_image(env.mlx.mlx, WIDTH, HEIGHT_PLANE);
	if (!env.mlx.s_image)
			return (write(2, "IMAGE FAILURE\n", 15));
	env.mlx.image = (int *)mlx_get_data_addr(env.mlx.mlx, &bpp, env.mlx.s_image, &endian);
	while(1);
	//display_map(env);
	//pas oublier de set les hooks
	//mlx_loop();
	//destroy_all(&env);
	return (0);
}
