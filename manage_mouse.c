#include "cub3D.h"

void	fixed_axe(double *axe_player, int tmp, int nb)
{
	(void) tmp;
	if (nb == 1)
	{
		*axe_player -= SPEED_MOUSE;
		if (*axe_player < 0)
			*axe_player += 360;
	}
	if (nb == 2)
	{
		*axe_player += SPEED_MOUSE;
		if (*axe_player > 359)
			*axe_player -= 360;
	}
}

void	check_mouse(t_env *env)
{
	int	x;
	int	y;
	int	tmp;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(env->mlx.mlx, env->mlx.mlx_win, &x, &y);
	if (x > WIDTH / 2)
	{
		tmp = x - (WIDTH / 2);
		tmp /= POV;
		fixed_axe(&env->map.axe_player, tmp, 1);
	}
	else if (x < WIDTH / 2)
	{
		tmp = (WIDTH / 2) - x;
		tmp /= POV;
		fixed_axe(&env->map.axe_player, tmp, 2);
	}
	mlx_mouse_move(env->mlx.mlx, env->mlx.mlx_win, WIDTH / 2, HEIGHT_PLANE / 2);
}
