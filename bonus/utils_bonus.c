/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils _bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 01:18:30 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/23 22:55:17 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	ft_memset(void *pointer, int value, size_t count)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)pointer;
	while (i < count)
	{
		p[i] = value;
		i++;
	}
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(ft_strlen((char *)str) + 1);
	while (str[j] == 32 || (str[j] <= 13 && str[j] >= 9))
		j++;
	while (str[j] && str[j] != '\n')
		new[i++] = str[j++];
	new[i] = 0;
	return (new);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c <= 13 && c >= 9))
		return (1);
	else
		return (0);
}
