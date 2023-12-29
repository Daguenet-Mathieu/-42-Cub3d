#include "cub3D.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
}

void	free_struct(t_env *env)
{
	if (env->mlx.image)
		mlx_destroy_image(env->mlx.mlx, env->mlx.s_image);
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

void	set_hooks_mlx(t_env *env)
{
	// void *ptr;
	// ptr = mlx_xpm_file_to_image(env->mlx.mlx, "pexels-photo-207142.xpm", &x, &y);
	env->map.texture_no.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.no, &env->map.texture_no.size_line, &env->map.texture_no.height);
	env->map.texture_so.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.so, &env->map.texture_so.size_line, &env->map.texture_so.height);
	env->map.texture_we.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.we, &env->map.texture_we.size_line, &env->map.texture_we.height);
	env->map.texture_ea.ptr = mlx_xpm_file_to_image(env->mlx.mlx, env->map.ea, &env->map.texture_ea.size_line, &env->map.texture_ea.height);
	printf("no = %p so = %p ea = %p we = %p\n", env->map.texture_no.ptr, env->map.texture_so.ptr, env->map.texture_ea.ptr, env->map.texture_we.ptr);
	printf("path == %s\n%s\n%s\n%s\n",  env->map.no,  env->map.so,  env->map.ea,  env->map.we);
	env->map.texture_no.img = (int *)mlx_get_data_addr(env->map.texture_no.ptr, &env->map.texture_no.bpp, &env->map.texture_no.size_line, &env->map.texture_no.endian);
	env->map.texture_so.img = (int *)mlx_get_data_addr(env->map.texture_so.ptr, &env->map.texture_so.bpp, &env->map.texture_so.size_line, &env->map.texture_so.endian);
	env->map.texture_we.img = (int *)mlx_get_data_addr(env->map.texture_we.ptr, &env->map.texture_we.bpp, &env->map.texture_we.size_line, &env->map.texture_we.endian);
    env->map.texture_ea.img = (int *)mlx_get_data_addr(env->map.texture_ea.ptr, &env->map.texture_ea.bpp, &env->map.texture_ea.size_line, &env->map.texture_ea.endian);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	mlx_mouse_hide(env->mlx.mlx, env->mlx.mlx_win);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	env->map.texture_no.size_line /= 4;
	env->map.texture_so.size_line /= 4;
	env->map.texture_we.size_line /= 4;
	env->map.texture_ea.size_line /= 4;
	//mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win,env->map.texture_no.ptr, 0, 0);
	//while(1);
}
