/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:02:10 by auferran          #+#    #+#             */
/*   Updated: 2023/12/21 19:47:38 by madaguen         ###   ########.fr       */
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
#define	FISHBOWL -30
#define PLAYER_HEIGHT 32
#define SIZE_CUBE 64
#define	WIDTH 1920
#define HEIGHT_PLANE 1080
#define NORTH 0x0000FF
#define SOUTH 0xFF0000
#define EAST 0xDAA520
#define WEST 0x7F00FF
#define FLOOR 0x70726E
#define SKY 0x2A303D
#define SPEED 1.5
#define	SPEED_2 3
#define SPEED_MOUSE 1
#define WIDTH_PLAYER 1
#define HEIGHT_PLAYER 1
#define BONUS 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 150
# endif

enum e_dir
{
	NO = 1,
	SO,
	WE,
	EA,
	EMPTY_LINE,
	C,
	F,
};

typedef struct	s_case
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	area_in_case;
}				t_case;

typedef struct s_img
{
	void	*ptr;
	int		size_line;
	int		height;
	int		*img;
	int		bpp;
	int		endian;
}			t_image;

typedef struct s_map
{
	char	**map;
	int		x_max;
	int		y_max;
	int		*img;
	double	pixel_x_player;
	double	pixel_y_player;
	double	axe_player;
	double	projection_plane;
	double	distance_wall;
	double	between_rays;
	int		ceiling;
	int		floor;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_image	texture_no;
	t_image	texture_so;
	t_image	texture_we;
	t_image	texture_ea;

}			t_map;

typedef struct s_print_wall
{
	int		i;
	double	height_draw;
	double	index_wall;
	double	ratio_leon;
	double	column_texture;
	double	diff;
	int		orientation;
	int		y_start;
}			t_print_wall;

typedef struct s_get_next_wall
{
	int		x;
	int		y;
	double	i;
	double	a_p;
	double	height;
	int		i_rayon;
}			t_get_next_wall;

typedef struct s_calcul
{
	double	new_x;
	double	new_y;
	double	old_x;
	double	old_y;
	int		grid_x;
	int		grid_y;
	double	ya;
	double	xa;
}			t_calcul;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_key;

typedef struct	s_pos
{
	double	new_y;
	double	new_x;
}			t_pos;

typedef struct	s_mlx
{
	int		*image;
	void	*mlx;
	void	*mlx_win;
	void	*s_image;
	int		win_x;
	int		win_y;
}				t_mlx;
typedef struct s_env
{
	t_mlx		mlx;
	t_map		map;
	t_calcul	h;
	t_calcul	v;
	t_key		key;
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

void	print_wall(t_env *env, t_get_next_wall wall);

void	find_wall_h(t_env *env, double a_p);
void	find_wall_v(t_env *env, double a_p);

int		its_wall(char **map, int grid_y, int grid_x);
double	calcul_projection_plane(void);
double	calcul_a_p(double axe_player);
void	recalcul_a_p(double *a_p, double between_rays);
double	calcul_distance(t_env *env, int *x, int *y);
void	remove_fishbowl(double *distance, double i);

int		init_mlx(t_mlx *mlx);
void	free_struct(t_env *env);
int		mlx_close(t_env *env);
void	set_hooks_mlx(t_env *env);


void	init_pos_l_r(t_pos *pos, t_env *env, int *move);
void	init_pos_t_d(t_pos *pos, t_env *env, int *move);
void	ajust_key_release(int *key1, int *key2);
int		handle_keyrelease(int key_code, t_env *env);
void	ajust_key_press(int *key1, int *key2);
int		handle_keypress(int key_code, t_env *env);
int		handle_key(t_env *env);
void	check_mouse(t_env *env);

void 	set_map(t_env *env);

void 	init_mp_info(t_map *map);

#endif
