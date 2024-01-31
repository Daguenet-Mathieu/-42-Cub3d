/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:52:08 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/31 00:29:03 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_sprite(t_env *env, char *img, t_image *i)
{
	i->ptr = mlx_xpm_file_to_image \
	(env->mlx.mlx, img, &i->size_line, &i->height);
}

int	*get_data(t_image *i)
{
	return ((int *)mlx_get_data_addr \
	(i->ptr, &i->bpp, &i->size_line, &i->endian));
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

int	get_weapon(t_env *env)
{
	const t_image	*i = env->map.gun.img;

	init_sprite(env, "img/weapon/gun/1.xpm", &env->map.gun.img[0]);
	init_sprite(env, "img/weapon/gun/2.xpm", &env->map.gun.img[1]);
	init_sprite(env, "img/weapon/gun/3.xpm", &env->map.gun.img[2]);
	init_sprite(env, "img/weapon/gun/4.xpm", &env->map.gun.img[3]);
	if (!i[0].ptr || !i[1].ptr || !i[2].ptr || !i[3].ptr)
		return (0);
	env->map.gun.img[0].img = get_data((t_image *)&env->map.gun.img[0]);
	env->map.gun.img[1].img = get_data((t_image *)&env->map.gun.img[1]);
	env->map.gun.img[2].img = get_data((t_image *)&env->map.gun.img[2]);
	env->map.gun.img[3].img = get_data((t_image *)&env->map.gun.img[3]);
	env->map.gun.img[0].size_line /= sizeof(int);
	env->map.gun.img[1].size_line /= sizeof(int);
	env->map.gun.img[2].size_line /= sizeof(int);
	env->map.gun.img[3].size_line /= sizeof(int);
	if ((int)W_SIZE)
	{
		if (!zoom_img((t_image *)&i[0], W_SIZE) || \
		!zoom_img((t_image *)&i[1], W_SIZE) || !zoom_img \
		((t_image *)&i[2], W_SIZE) || !zoom_img((t_image *)&i[3], W_SIZE))
			return (0);
	}
	env->map.gun.cur_img = env->map.gun.img[0];
	return (1);
}

int	init_img(t_env *env)
{
	env->map.t_no.ptr = mlx_xpm_file_to_image(env->mlx.mlx, \
	env->map.no, &env->map.t_no.size_line, &env->map.t_no.height);
	env->map.t_so.ptr = mlx_xpm_file_to_image(env->mlx.mlx, \
	env->map.so, &env->map.t_so.size_line, &env->map.t_so.height);
	env->map.t_we.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.we, \
	&env->map.t_we.size_line, &env->map.t_we.height);
	env->map.t_ea.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.ea, \
	&env->map.t_ea.size_line, &env->map.t_ea.height);
	if (!env->map.t_no.ptr || !env->map.t_so.ptr || \
	!env->map.t_ea.ptr || !env->map.t_we.ptr)
		return (0);
	env->map.t_no.img = (int *)mlx_get_data_addr(env->map.t_no.ptr, \
	&env->map.t_no.bpp, &env->map.t_no.size_line, &env->map.t_no.endian);
	env->map.t_so.img = (int *)mlx_get_data_addr(env->map.t_so.ptr, \
	&env->map.t_so.bpp, &env->map.t_so.size_line, &env->map.t_so.endian);
	env->map.t_we.img = (int *)mlx_get_data_addr(env->map.t_we.ptr, \
	&env->map.t_we.bpp, &env->map.t_we.size_line, &env->map.t_we.endian);
	env->map.t_ea.img = (int *)mlx_get_data_addr(env->map.t_ea.ptr, \
	&env->map.t_ea.bpp, &env->map.t_ea.size_line, &env->map.t_ea.endian);
	return (1);
}
