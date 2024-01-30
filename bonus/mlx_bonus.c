/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:05:22 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/30 02:59:27 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	destroy_gun(t_env *env, t_gun gun)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (gun.img[i].ptr)
			mlx_destroy_image(env->mlx.mlx, gun.img[i].ptr);
		if (gun.img[i].new_img)
		free(gun.img[i].new_img);
		i++;
	}
}

void	free_struct_util(t_env *env)
{
	if (env->mini.img)
		free (env->mini.img);
	if (env->mini.map)
		free (env->mini.map);
	if (env->map.no)
		free(env->map.no);
	if (env->map.so)
		free(env->map.so);
	if (env->map.we)
		free(env->map.we);
	if (env->map.ea)
		free(env->map.ea);
	if (env->map.cpy_c_f)
		free(env->map.cpy_c_f);
}

void	free_struct(t_env *env)
{
	free_struct_util(env);
	if (env->map.door.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.door.ptr);
	if (env->map.door1)
		free (env->map.door1);
	destroy_gun(env, env->map.gun);
	if (env->mlx.s_image)
		mlx_destroy_image(env->mlx.mlx, env->mlx.s_image);
	if (env->map.t_no.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_no.ptr);
	if (env->map.t_so.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_so.ptr);
	if (env->map.t_we.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_we.ptr);
	if (env->map.t_ea.ptr)
		mlx_destroy_image(env->mlx.mlx, env->map.t_ea.ptr);
	if (env->mlx.mlx_win)
		mlx_destroy_window(env->mlx.mlx, env->mlx.mlx_win);
	if (env->mlx.mlx)
		mlx_destroy_display(env->mlx.mlx);
	if (env->mlx.mlx)
		mlx_loop_end(env->mlx.mlx);
	free(env->mlx.mlx);
	free_tab(env->map.map);
	exit(0);
}


int	mlx_close(t_env *env)
{
	write(1, "\n", 1);
	free_struct(env);
	return (0);
}

void	init_sprite(t_env *env, char *img, t_image *i)
{
	i->ptr = mlx_xpm_file_to_image(env->mlx.mlx, img, &i->size_line, &i->height);
}

int	*get_data(t_image *i)
{
	return ((int *)mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian));
}

void	get_coord(char **map, t_door *doors)
{
	int	d;
	int	i;
	int	j;

	j = 0;
	d = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'd')
			{
				doors[d].x = i;
				doors[d].y = j;
				d++;
			}
			i++;
		}
		j++;
	}
}

int	init_door(t_env *env)
{
	int	i;

	env->map.door1 = malloc(sizeof(t_door) * env->map.nb_door);
	if (!env->map.door1)
		return (0);
	get_coord(env->map.map, env->map.door1);
	i = 0;
	while (i < env->map.nb_door)
	{
		env->map.door1[i].time_start = ft_get_time();
		env->map.door1[i].interval = DOOR_TIME / 100;
		env->map.door1[i].anim_state = 100;
		env->map.door1[i].is_openning = CLOSE;
		env->map.door1[i].img = env->map.door;
		i++;
	}
	return (1);
}


int	get_door(t_env *env)
{
	init_sprite(env,"img/door/1.xpm", &env->map.door);
	if (!env->map.door.ptr)
		return (0);
	env->map.door.img = get_data(&env->map.door);
	env->map.door.size_line /= 4;
	if (!init_door(env))
		return (0);
	return (1);
}

int zoom_img(t_image *img, double zoom)
{
    int l;
    int c;
    int l_ratio;
	int c_ratio;
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
    	while (c < img->new_size_line)
        {
			l_ratio = (int)(l / zoom);
			c_ratio = (int)(c / zoom);
           	pixel = img->img[(int)(l_ratio * img->size_line + c_ratio)];
          	img->new_img[l * img->new_size_line + c] = pixel;
            c++;
		}
        l++;
    }

    return (1);
}

int get_weapon(t_env *env)
{
	const t_image *i = env->map.gun.img;

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
		if (!zoom_img((t_image *)&i[0], W_SIZE) || !zoom_img((t_image *)&i[1], W_SIZE) || \
		!zoom_img((t_image *)&i[2], W_SIZE) || !zoom_img((t_image *)&i[3], W_SIZE))
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

int	init_shading_map(t_env * env)
{
	env->map.cpy_c_f = malloc(sizeof(int) * (WIDTH * HEIGHT_PLANE));
	if (!env->map.cpy_c_f)
		return (0);
	set_map(env, env->map.cpy_c_f);
	return (1);
}

int	set_hooks_mlx(t_env *env)
{
	if (!init_img(env) || !get_door(env) || !get_weapon(env))
		return (write(2, "fail to load img\n", 18), 0);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	if (LEAK == 1)
		mlx_mouse_hide(env->mlx.mlx, env->mlx.mlx_win);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	env->map.t_no.size_line /= 4;
	env->map.t_so.size_line /= 4;
	env->map.t_we.size_line /= 4;
	env->map.t_ea.size_line /= 4;
	if (!init_shading_map(env))
		return (0);
	return (1);
}
