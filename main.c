/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:18:22 by auferran          #+#    #+#             */
/*   Updated: 2023/12/19 09:55:26 by auferran         ###   ########.fr       */
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

void set_map(t_env *env)
{
	int y;
	int i;

	i = 0;
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

int	main(int argc, char **argv)
{
	//int		i;
	//int		y;
	int		bpp;
	int		endian;
	int	size_line = WIDTH;
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	if (argc != 2)
		return (write(2, "Incorrect number of arguments\n", 31));
	if (!get_map(&env.map, argv[1]))
		return (1);
	get_pos_player(&env.map);
	init_mp_info(&env.map);
	env.mlx.mlx = mlx_init();
	if (!env.mlx.mlx)
		return (write(2, "MLX FAILURE\n", 13));
	env.mlx.mlx_win = mlx_new_window(env.mlx.mlx, WIDTH, HEIGHT_PLANE, "cub3D");
	if (!env.mlx.mlx_win)
		return (write(2, "WINDOW FAILURE\n", 16));
	env.mlx.s_image = mlx_new_image(env.mlx.mlx, WIDTH, HEIGHT_PLANE);
	if (!env.mlx.s_image)
			return (write(2, "IMAGE FAILURE\n", 15));
	env.mlx.image = (int *)mlx_get_data_addr(env.mlx.s_image, &bpp, &size_line, &endian);
	//printf("plafond == %x sol == %x\n",env.map.ceiling, env.map.floor);
	set_hooks_mlx(&env);
	set_map(&env);
	get_next_wall(&env);
	mlx_loop(env.mlx.mlx);
	/*int i = 0;
	int	k = 0;
	int j = 0;
	int *ptr = env.mlx.image;
	while (j < env.map.texture_no.height)
	{
		ptr[k] = env.map.texture_no.img[i];
		i++;
		if (i == env.map.texture_no.size_line)
		{
			env.map.texture_no.img += env.map.texture_no.size_line;
			ptr += WIDTH;
			i = 0;
			k = 0;
			j++;
		}
		else
		{
			i++;
			k++;
		}
	}*/

	// int	i = 0;
	// int	j = 0;
	// int	k = 0;
	 //int *ptr = env.mlx.image;
	 //int o;
	//  while (j < env.map.texture_no.height)
	//  {
	//  	printf("j = %d\n", j);
	//  	printf("map.texture_no.height = %d\n", env.map.texture_no.height);
	// 	printf("map.texture_no.size_line = %d\n", env.map.texture_no.size_line);
	// 	i = 0;
	// 	o = 0;
	//  	while (i < env.map.texture_no.size_line)
	//  	{
	//  		ptr[o] = env.map.texture_no.img[k + i];
	//  		i += 8;
	// 		o++;
	//  	}
	//  	j += 8;
	//  	k = k + (env.map.texture_no.size_line * 8);
	//  	ptr += WIDTH;
	//  }
	//while (i < env.map.texture_no.size_line)
	//{
		//j = 0;
		//o = 0;
		//while (j < 720 * env.map.texture_no.size_line/*env.map.texture_no.height*/)
		//{
		//	ptr[o] = env.map.texture_no.img[k + j];
	 	//	j += (env.map.texture_no.size_line * 7);
		//	o += WIDTH;
		//}
	 	//i+=7;
	 	//k+=7;
	 	//ptr++;
	//}
	//mlx_put_image_to_window(env.mlx.mlx,env.mlx.mlx_win, env.mlx.s_image, 0, 0);
	//while(1)
	//	;
	//display_map(env);
	//mlx_loop();
	//destroy_all(&env);
	return (0);
}
