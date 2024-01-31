/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:51:53 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/31 00:31:33 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	init_sprite(env, "img/door/1.xpm", &env->map.door);
	if (!env->map.door.ptr)
		return (0);
	env->map.door.img = get_data(&env->map.door);
	env->map.door.size_line /= 4;
	if (!init_door(env))
		return (0);
	return (1);
}
