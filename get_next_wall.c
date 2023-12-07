/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:24:24 by madaguen          #+#    #+#             */
/*   Updated: 2023/12/05 18:36:13 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_next_wall(t_env *env)
{
	double	i;
	double	a_p;
	double	distance;
	double	hauteur_tranche;

	(void)distance;
	(void)hauteur_tranche;
	env->map.projection_plane = calcul_projection_plane();
	env->map.between_rays = (double)POV / (double)WIDTH;
	a_p = calcul_a_p(env->map.axe_player);
	i = POV / 2;
	while (i > ((double)POV / 2 * -1))
	{
		find_wall_h(env, a_p);
		find_wall_v(env, a_p);
		distance = calcul_distance(env);
		remove_fishbowl(&distance, i);
		hauteur_tranche = (SIZE_CUBE / distance) * env->map.projection_plane;
		recalcul_a_p(&a_p, env->map.between_rays);
		i = i - env->map.between_rays;
	}
	//maintenant trouver la hauteur de la tranche du mur avec :
	// Une fois cela calculé, la tranche de mur peut être dessinée sur l'écran.
	//Cela peut être fait en traçant simplement une ligne verticale sur
	//la colonne correspondante sur le plan de projection
}
