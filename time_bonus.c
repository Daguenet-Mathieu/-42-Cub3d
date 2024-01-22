#include "cub3D_bonus.h"

unsigned long long ft_get_time()
{
	struct timeval		tv;
	if (gettimeofday(&tv, (void *)0) == -1)
		return (-1);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	check_time(unsigned long long time, unsigned long long interval)
{
	unsigned long long	new_time;

	new_time = ft_get_time();
	if (new_time == -1)
		return (-1);
	if (time + interval < new_time)
		return (1);
	else
		return (0);
}