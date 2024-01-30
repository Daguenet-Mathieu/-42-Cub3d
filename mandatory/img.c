/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 02:44:50 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/30 02:48:43 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sprite(t_env *env, char *img, t_image *i)
{
	i->ptr = mlx_xpm_file_to_image(env->mlx.mlx, img, \
	&i->size_line, &i->height);
}

int	*get_data(t_image *i)
{
	return ((int *)mlx_get_data_addr(i->ptr, &i->bpp, \
	&i->size_line, &i->endian));
}

int	zoom_img(t_image *img, double zoom)
{
	int	l;
	int	c;
	int	l_ratio;
	int	c_ratio;
	int	pixel;

	img->new_size_line = (int)(img->size_line * zoom);
	img->new_height = (int)(img->height * zoom);
	img->new_img = malloc((img->new_size_line * img->new_height) * sizeof(int));
	if (!img->new_img)
		return (0);
	l = 0;
	while (l < img->new_height)
	{
		c = 0;
		l_ratio = (int)(l / zoom);
		while (c < img->new_size_line)
		{
			c_ratio = (int)(c / zoom);
			pixel = img->img[(int)(l_ratio * img->size_line + c_ratio)];
			img->new_img[l * img->new_size_line + c++] = pixel;
		}
		l++;
	}
	return (1);
}
