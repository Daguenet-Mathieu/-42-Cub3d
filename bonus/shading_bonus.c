/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:58:09 by auferran          #+#    #+#             */
/*   Updated: 2024/01/30 00:03:57 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	get_rgb(int	color, int *red, int *green, int *blue)
{
	*red = (color>>16) & 0xFF;
	*green = (color>>8) & 0xFF;
	*blue = color & 0xFF;
}

int	get_shading_wall(int red, int green, int blue, double distance_wall)
{
	double	factor;

	factor = (1.0 / distance_wall) * 150;
	red = (int)((double)red * factor);
	green = (int)((double)green * factor);
	blue = (int)((double)blue * factor);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return (red<<16 | green<<8 | blue);
}

int	get_shading_floor_ceiling(int red, int green, int blue, int y)
{
	double	factor;

	y += 300;
	factor = (1.0 / y) * 150;
	red = (int)((double)red * factor);
	green = (int)((double)green * factor);
	blue = (int)((double)blue * factor);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return (red<<16 | green<<8 | blue);
}

int	c_f_shading(int color, int y)
{
	int	red;
	int	green;
	int	blue;
	int	new_color;

	get_rgb(color, &red, &green, &blue);
	new_color = get_shading_floor_ceiling(red, green, blue, y);
	return (new_color);
}
