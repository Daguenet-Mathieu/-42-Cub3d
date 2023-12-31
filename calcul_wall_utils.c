/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:35:12 by auferran          #+#    #+#             */
/*   Updated: 2023/12/19 10:33:50 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	size_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	its_wall(char **map, int grid_y, int grid_x)
{
	if (grid_y < 0 || grid_x < 0)
		return (1);
	if (grid_y > (size_map(map) - 1))
		return (1);
	else if (grid_x > ft_strlen(map[grid_y]))
		return (1);
	if (map[grid_y][grid_x] == '1')
		return (1);
	return (0);
}

double	calcul_a_p(double axe_player)
{
	double	a_p;
	double	tmp;

	if (axe_player > 329)
	{
		tmp = axe_player + (POV / 2);
		a_p = tmp - 360;
	}
	else
		a_p = axe_player + (POV / 2);
	return (a_p);
}

void	recalcul_a_p(double *a_p, double between_rays)
{
	*a_p = *a_p - between_rays;
	if (*a_p < 0)
		*a_p = *a_p + 360;
}

double	calcul_distance(t_env *env, int *x, int *y)
{
	double			d;
	double			d_h;
	double			d_v;

	*y = -1;
	*x = -1;
	d_h = sqrt(pow((double)env->map.pixel_x_player - (double)env->h.new_x, 2)
		+ pow((double)env->map.pixel_y_player - (double)env->h.new_y, 2));
	d_v = sqrt(pow((double)env->map.pixel_x_player - (double)env->v.new_x, 2)
		+ pow((double)env->map.pixel_y_player - (double)env->v.new_y, 2));
	if (d_h <= d_v)
	{
		*y = env->h.new_y;
		d = d_h;
	}
	else
	{
		*x = env->v.new_x;
		d = d_v;
	}
	return (d);
}
