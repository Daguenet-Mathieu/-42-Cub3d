/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:18:22 by auferran          #+#    #+#             */
/*   Updated: 2023/09/15 19:54:46 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		return (error("Incorrect nunmber of arguments\n"));
	if (!get_map(&env.map, argv[1]))
		return (1);
	if (!init_mlx(&env.mlx))
		return (1);
	//display_map(env);
	//pas oublier de set les hooks
	//mlx_loop();
	//destroy_all(&env);
	return (0);
}
