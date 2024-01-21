/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:48:08 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/21 17:59:59 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	ptr_offset(int l, int c, int width, int s_cub)
{
	return ((l * s_cub * width) + (c * s_cub));
}

void	ft_set(void *ptr, int value, int size)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)ptr;
	while (i < size)
	{
		p[i] = value;
		i++;
	}
}
