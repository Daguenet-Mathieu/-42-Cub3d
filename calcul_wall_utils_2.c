/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_wall_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:35:20 by auferran          #+#    #+#             */
/*   Updated: 2023/12/08 15:35:21 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	remove_fishbowl(double *distance, double i)
{
	double	c;
	double	tmp;
	double	angle;

	angle = ((i * M_PI) / 180);
	c = cos(angle);
	tmp = *distance;
	*distance = tmp * c;
}
