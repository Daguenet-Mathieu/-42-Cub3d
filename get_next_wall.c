/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:24:24 by madaguen          #+#    #+#             */
/*   Updated: 2023/12/02 07:00:15 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calcul_projection_plane(void)
{
	double	nb;
	double	angle;
	double	t;

	angle = ((POV * M_PI) / 180);
	t = tan(angle / 2);
	nb = (WIDTH / 2) / t;
	return (nb);
}

void	get_next_wall(t_env *env)
{
	double			c;
	double			angle;
	unsigned int	distance_h;
	unsigned int	distance_v;
	unsigned int	distance;
	int				hauteur_tranche;

	angle = ((POV * M_PI) / 180);
	c = cos(angle);
	env->map.projection_plane = calcul_projection_plane();
	env->map.between_rays = POV / WIDTH;
	// Pour chaque rayon appelez :
	find_wall_h(env);
	find_wall_v(env);
	//incrementer env->map.axe_player
	//ensuite comparer la distance entre les deux pour savoir lequel dessiner :
	distance_h = (env->map.pixel_x_player - env->h.new_x) / c;
	distance_v = (env->map.pixel_x_player - env->v.new_x) / c;
	if (distance_h >= distance_v)
		distance = distance_h;
	else
		distance = distance_v;

	// s'occuper de l'effet fishbowl pour eviter distorsion
	//multiplier distance par cos(POV_2) ou POV_2 est l'angle du rayson par rapport a langle de vue
	//entre -30 et 30 ?

	//maintenant trouver la hauteur de la tranche du mur avec :
	hauteur_tranche = SIZE_CUBE / distance * env->map.projection_plane;
	// Une fois cela calculé, la tranche de mur peut être dessinée sur l'écran.
	//Cela peut être fait en traçant simplement une ligne verticale sur
	//la colonne correspondante sur le plan de projection

	//continuer fin de la PART 9
}
