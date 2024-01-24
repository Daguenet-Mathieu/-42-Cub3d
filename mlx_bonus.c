/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:05:22 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/24 06:41:37 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
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
}

void	free_struct(t_env *env)
{
	free_struct_util(env);
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

int	get_door(t_env *env)
{
	(void) env;
	return (1);
}

// int zoom_img(t_image *img, double zoom)
// {
//     double  ratio;
//     double  j;
//     int     i;
//     int     size;

//     size = img->size_line * img->height;
//     img->new_size_line = img->size_line * zoom;
//     img->new_height = img->height * zoom;
//     img->new_img = malloc((img->new_size_line * img->new_height) * sizeof(int));
//     if (!img->new_img)
//         return (0);
//     ratio = 1 / zoom;
//     i = 0;
//     j = 0;
//     printf("ratio == %f\n", ratio);
//     while ((int)j < size && i < (img->new_size_line * img->new_height))
//     {
//         printf("i == %d j == %f j== %d\n", i, j, (int)j);
//         printf("size == %d , new size == %d\n", size,  (img->new_size_line * img->new_height));
//         int test = img->new_img[i];
//         (void) test;
//         int test2 = img->img[(int)j];
//         (void) test2;
//         j += ratio;
//         i++;
//     }
//     return (1);
// }

// int zoom_img(t_image *img, double zoom)
// {
//      double  ratio;
//      int     i;
//      double  l;
//      double  c;
//      int     size;

//      size = img->size_line * img->height;
//      img->new_size_line = (int)(img->size_line * zoom);
//      img->new_height = (int)(img->height * zoom);
//      img->new_img = malloc((img->new_size_line * img->new_height) * sizeof(int));
//     if (!img->new_img)
//         return (0);

//      ratio = 1 / zoom;
//      i = 0;
//      l = 0;
// 	 c = 0;
//      while (l < img->height)
//      {
// 		//printf("cur index == %f\n", l*img->new_size_line);
// 		 printf("i == %d c == %f l == %f nbr line == %d\n", i/img->new_size_line, c, l, img->new_size_line);
//          c = 0;
// 		//printf("size == %d , new size == %d\n", size,  (img->new_size_line * img->new_height));
// 		//printf("---> %d\n", img->new_size_line);
// 			printf("rario == %f ---> %d, i == %d, nsize == %d, old == %d\n", ratio, img->new_size_line, i, img->new_size_line * img->new_height, size);
//         while (c < img->size_line)
//          {
// 			printf("c == %f, index == %d\n", c, (int)(l * img->size_line + c));
//              int new_pixel_value = img->img[(int)(l * img->size_line + c)];
//              img->new_img[i] = new_pixel_value;
//              c += ratio;
//              i++;
//          }
//          l += ratio;
//      }

//      return (1);
// }

int zoom_img(t_image* img, double zoom) {
    img->new_size_line = (int)(img->size_line * zoom);
    img->new_height = (int)(img->height * zoom);
    img->new_img = malloc(img->new_size_line * img->new_height * sizeof(int));

    if (!img->new_img) {
        return 0;
    }

    for (int l = 0; l < img->new_height; l++) {
        for (int c = 0; c < img->new_size_line; c++) {
            int original_row = (int)(l / zoom);
            int original_col = (int)(c / zoom);
            int original_pixel_value = img->img[original_row * img->size_line + original_col];
            img->new_img[l * img->new_size_line + c] = original_pixel_value;
        }
    }

    return 1;
}

int get_weapon(t_env *env)
{
    env->map.gun.img[0].ptr = mlx_xpm_file_to_image(env->mlx.mlx, "img/weapon/gun/1.xpm", &env->map.gun.img[0].size_line, &env->map.gun.img[0].height);
    env->map.gun.img[1].ptr = mlx_xpm_file_to_image(env->mlx.mlx, "img/weapon/gun/2.xpm", &env->map.gun.img[1].size_line, &env->map.gun.img[1].height);
    env->map.gun.img[2].ptr = mlx_xpm_file_to_image(env->mlx.mlx, "img/weapon/gun/3.xpm", &env->map.gun.img[2].size_line, &env->map.gun.img[2].height);
    env->map.gun.img[3].ptr = mlx_xpm_file_to_image(env->mlx.mlx, "img/weapon/gun/4.xpm", &env->map.gun.img[3].size_line, &env->map.gun.img[3].height);
	if (!env->map.gun.img[0].ptr || !env->map.gun.img[1].ptr || !env->map.gun.img[2].ptr || !env->map.gun.img[3].ptr)
        return (0);
    env->map.gun.img[0].img = (int *)mlx_get_data_addr(env->map.gun.img[0].ptr, &env->map.gun.img[0].bpp, &env->map.gun.img[0].size_line, &env->map.gun.img[0].endian);
    env->map.gun.img[1].img = (int *)mlx_get_data_addr(env->map.gun.img[1].ptr, &env->map.gun.img[1].bpp, &env->map.gun.img[1].size_line, &env->map.gun.img[1].endian);
    env->map.gun.img[2].img = (int *)mlx_get_data_addr(env->map.gun.img[2].ptr, &env->map.gun.img[2].bpp, &env->map.gun.img[2].size_line, &env->map.gun.img[2].endian);
    env->map.gun.img[3].img = (int *)mlx_get_data_addr(env->map.gun.img[3].ptr, &env->map.gun.img[3].bpp, &env->map.gun.img[3].size_line, &env->map.gun.img[3].endian);

	
	env->map.gun.img[0].size_line /= sizeof(int);
	env->map.gun.img[1].size_line /= sizeof(int);
	env->map.gun.img[2].size_line /= sizeof(int);
	env->map.gun.img[3].size_line /= sizeof(int);
   if ((int)WEAPON_RESIZE)
   {
   	if (!zoom_img(&env->map.gun.img[0], WEAPON_RESIZE) || !zoom_img(&env->map.gun.img[1], WEAPON_RESIZE) || !zoom_img(&env->map.gun.img[2], WEAPON_RESIZE) || !zoom_img(&env->map.gun.img[3], WEAPON_RESIZE))
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

int	set_hooks_mlx(t_env *env)
{
	if (!init_img(env) || !get_door(env) || !get_weapon(env))
		return (write(2, "fail to load img\n", 18), 0);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	if (BONUS == 1)
		mlx_mouse_hide(env->mlx.mlx, env->mlx.mlx_win);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	env->map.t_no.size_line /= 4;
	env->map.t_so.size_line /= 4;
	env->map.t_we.size_line /= 4;
	env->map.t_ea.size_line /= 4;
	return (1);
}
