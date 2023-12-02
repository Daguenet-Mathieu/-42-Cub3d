/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:24:24 by madaguen          #+#    #+#             */
/*   Updated: 2023/12/02 07:00:15 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_next_wall(t_env *env)
{
	(void) env;
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle / 2);
	env->map.distance_wall = (WIDTH / 2) / t;
}