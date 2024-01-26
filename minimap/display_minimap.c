/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:42:44 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/25 23:01:23 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	set_square_minimap(t_minimap mini, double x, double y)
{
	t_display_minimap	m;

	m.ptr = mini.img;
	ft_set(mini.img, 0, (mini.height_img * mini.width_img) * sizeof(int));
	m.p_x = (x * M_SIZE) - (mini.height_img / 2);
	m.p_y = (y * M_SIZE) - (mini.width_img / 2);
	m.j = 0;
	while (m.j < mini.height_img)
	{
		m.i = 0;
		while (m.i < mini.width_img)
		{
			if ((m.p_x + m.j >= 0 && m.p_y + m.i >= 0) && \
				(m.p_x + m.j < mini.height && m.p_y + m.i < mini.width))
				m.ptr[m.j * mini.width_img + m.i] = \
				mini.map[(m.p_x + m.j) * mini.width + (m.p_y + m.i)];
			m.i++;
		}
		m.j++;
	}
}

void	set_circle_minimap(t_minimap mini)
{
	t_display_minimap	m;

	m.a = mini.height_img / 2 - mini.radius;
	m.i = 0;
	m.ptr = mini.img;
	m.x = 0;
	m.y = 0;
	while (m.x < mini.width_img)
	{
		m.b = mini.width_img / 2 - mini.radius;
		while (m.y < mini.height_img)
		{
			if (!(((m.b - mini.radius) * (m.b - mini.radius)) + \
				((m.a - mini.radius) * (m.a - mini.radius))
					<= (mini.radius * mini.radius)))
				m.ptr[m.i] = TRANSPARENT;
			m.i++;
			m.b++;
		}
		m.a++;
	}
}

void	init_circle(t_minimap mini)
{
	t_display_minimap	m;

	m.y = 0;
	m.i = 0;
	m.ptr = mini.img;
	while (m.y < mini.height_img)
	{
		m.x = 0;
		while (m.x < mini.width_img)
		{
			if (!(((m.x - mini.radius) * (m.x - mini.radius)) + \
			((m.y - mini.radius) * (m.y - mini.radius)) \
			<= (mini.radius * mini.radius)))
				m.ptr[m.i] = TRANSPARENT;
			m.i++;
			m.x++;
		}
		m.y++;
	}
}

void	print_mini_player(int *ptr, double p_x, double p_y, t_minimap mini)
{
	p_y = p_y * M_SIZE;
	p_x = p_x * M_SIZE;
	ptr += (mini.width_img * mini.height_img / 2) + (mini.width_img / 2);
	*ptr = WHITE;
	*(ptr + 1) = WHITE;
	*(ptr + mini.width_img) = WHITE;
	*((ptr + mini.width_img) + 1) = WHITE;
}

void	print_minimap(t_minimap mini, int *ptr, int width)
{
	int	i;
	int	j;

	i = 0;
	ptr += (MARGIN * width + MARGIN);
	while (i < (mini.height_img))
	{
		j = 0;
		while (j < mini.width_img)
		{
			if ((unsigned int)mini.img[i * mini.width_img + j] != TRANSPARENT)
				ptr[i * width + j] = mini.img[i * mini.width_img + j];
			j++;
		}
		i++;
	}
}
