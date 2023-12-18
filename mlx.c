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
	// int x;
	// int y;
	// ptr = mlx_xpm_file_to_image(env->mlx.mlx, "pexels-photo-207142.xpm", &x, &y);
	env->map.texture_no.ptr = mlx_xpm_file_to_image(env->mlx.mlx, "pexels-photo-207142.xpm", &env->map.texture_no.size_line, &env->map.texture_no.height);
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	mlx_hook(env->mlx.mlx_win, 6, 1L << 6, (int (*)(t_env *env))mouse_movement, env);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
	//printf("x == %d, y == %d\n", env->map.texture_no->size_line, env->map.texture_no->height);
	//mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win,env->map.texture_no, x, y);
}
