/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:02:10 by auferran          #+#    #+#             */
/*   Updated: 2023/12/02 06:59:39 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "mlx_linux/mlx.h"
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>


#define POV 60
#define PLAYER_HEIGHT 32
#define SIZE_CUBE 64
#define	WIDTH 320
#define HEIGHT_PLANE 200

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 150
# endif

typedef struct s_map
{
	char			**map;
	unsigned int	x_player;
	unsigned int	y_player;
	unsigned int	pixel_x_player;
	unsigned int	pixel_y_player;
	double			axe_player;
	double			projection_plane;
	double			distance_wall;
	double			between_rays;
}					t_map;

typedef struct s_calcul
{
	int				new_x;
	int				new_y;
	int				old_x;
	int				old_y;
	int				grid_x;
	int				grid_y;
	int				ya;
	int				xa;
}					t_calcul;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_key;

typedef struct	s_mlx
{
	int		*image;
	void	*mlx;
	void	*mlx_win;
	int		win_x;
	int		win_y;
}				t_mlx;
typedef struct s_env
{
	t_mlx		mlx;
	t_map		map;
	t_calcul	h;
	t_calcul	v;
}			t_env;

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}					t_lst;

int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_memset(void *pointer, int value, size_t count);
char	*get_next_line(int fd);

int		get_map(t_map *map, char *map_title);

int		add_to_list(char *line, t_lst **lst);
void	del_one(t_lst **lst, t_lst *node);
void	lst_clear(t_lst **lst);
int		lst_size(t_lst *lst);
char	**lst_to_tab(t_lst *lst);

void	get_pos_player(t_map *map);

void	get_next_wall(t_env *env);

int		find_wall_h(t_env *env);
int		find_wall_v(t_env *env);

int		init_mlx(t_mlx *mlx);

#endif
