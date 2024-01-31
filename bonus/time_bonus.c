/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:29:19 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/31 00:30:48 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

unsigned long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, (void *)0) == -1)
		return (-1);
	return ((tv.tv_sec * 1000000) + (tv.tv_usec));
}

int	check_time(unsigned long long time, unsigned long long interval)
{
	unsigned long long	new_time;

	new_time = ft_get_time();
	if (new_time == (unsigned long long)-1)
		return (-1);
	if ((time + interval) < new_time)
		return (1);
	else
		return (0);
}
