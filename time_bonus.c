#include "cub3D_bonus.h"

unsigned long long ft_get_time()
{
	struct timeval		tv;
	if (gettimeofday(&tv, (void *)0) == -1)
		return (-1);
	return (tv.tv_sec * 1000000) + (tv.tv_usec);
}

int	check_time(unsigned long long time, unsigned long long interval)
{
	unsigned long long	new_time;

	new_time = ft_get_time();
	if (new_time == (unsigned long long)-1)
		return (-1);
	printf("start == %llu, interval == %llu, newtime == %llu\n", time , interval, new_time);
	if ((time + interval) < new_time)
		return (1);
	else
		return (0);
}