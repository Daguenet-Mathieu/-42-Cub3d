/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:02:10 by auferran          #+#    #+#             */
/*   Updated: 2023/09/15 20:12:48 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef CASE_SIZE
#  define CASE_SIZE 64
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 150
# endif

typedef struct s_map
{
	char			**map;
	unsigned int	height;
	unsigned int	width;
	unsigned int	x_player;
	unsigned int	y_player;
	double			axe_player;
}					t_map;

typedef struct s_env
{
	t_mlx	mlx;
	t_map	map;
}			t_env;

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}					t_lst;

void	*ft_memset(void *pointer, int value, size_t count);

int		error(char *str);

int		get_map(t_map *map, char *map_title);
char	**read_map(int fd);

int		init_mlx(t_mlx *mlx);

#endif
