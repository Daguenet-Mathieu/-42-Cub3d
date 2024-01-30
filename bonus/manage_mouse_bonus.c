/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mouse _bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:04:41 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/23 22:54:54 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	fixed_axe(double *axe_player, int nb)
{
	if (nb == 1)
	{
		*axe_player -= SPEED_MOUSE;
		if (*axe_player < 0)
			*axe_player += 360;
	}
	if (nb == 2)
	{
		*axe_player += SPEED_MOUSE;
		if (*axe_player > 359)
			*axe_player -= 360;
	}
}

void	check_mouse(t_env *env)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(env->mlx.mlx, env->mlx.mlx_win, &x, &y);
	if (x > WIDTH / 2)
		fixed_axe(&env->map.axe_player, 1);
	else if (x < WIDTH / 2)
		fixed_axe(&env->map.axe_player, 2);
	mlx_mouse_move(env->mlx.mlx, env->mlx.mlx_win, WIDTH / 2, HEIGHT_PLANE / 2);
}
