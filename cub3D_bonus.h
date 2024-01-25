/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:02:10 by auferran          #+#    #+#             */
/*   Updated: 2024/01/25 20:10:35 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "mlx_linux/mlx.h"
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
 #include <sys/time.h>
# include "minimap/minimap.h"

# define POV 60
# define FISHBOWL -30
# define PLAYER_HEIGHT 32
# define SIZE_CUBE 64
# define WIDTH 1920
# define HEIGHT_PLANE 1080
# define NORTH 0x0000FF
# define SOUTH 0xFF0000
# define EAST 0xDAA520
# define WEST 0x7F00FF
# define FLOOR 0x70726E
# define SKY 0x2A303D
# ifndef SPEED
#  define SPEED 1
# endif
# define SPEED_2 3
# define SPEED_MOUSE 5
# define MARGIN 50
# define WIDTH_PLAYER 1
# define HEIGHT_PLAYER 1
# define BONUS 1
# define WEAPON_RESIZE 3.5
# define GUN_TIME 500000
# define DOOR_TIME 3000000
# define WHITE 0XFFFFFF
# ifndef LEAK
#  define LEAK 0
# endif

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

enum e_anim_state
{
	OFF,
	ON_TOP,
	ON_DOWN,
};

enum e_door_state
{
	OPEN,
	CLOSE,
};


typedef struct s_case
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	area_in_case;
}	t_case;

typedef struct s_img
{
	void				*ptr;
	int					size_line;
	int					new_size_line;
	int					height;
	int					new_height;
	int					*img;
	int					*new_img;
	int					bpp;
	int					endian;
}	t_image;

typedef struct s_gun
{
	t_image				img[4];
	t_image				cur_img;
	unsigned long long	time_start;
	unsigned long long	interval;
	int					curr_img;
	int					anim_state;
}	t_gun;

typedef struct s_door
{
	t_image				img;
	unsigned long long	time_start;
	unsigned long long	interval;
	int					anim_state;
	int					is_open;
}	t_door;

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
	int		*cpy_c_f;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_image	t_no;
	t_image	t_so;
	t_image	t_we;
	t_image	t_ea;
	t_gun	gun;
	t_door	door1;
	t_door	door2;
}	t_map;

typedef struct s_print_wall
{
	int		i;
	double	height_draw;
	double	index_wall;
	double	ratio_leon;
	double	column_t;
	double	diff;
	int		orientation;
	int		y_start;
}	t_print_wall;

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
	int	space;
}	t_key;

typedef struct s_pos
{
	double	new_y;
	double	new_x;
}	t_pos;

typedef struct s_mlx
{
	int		*image;
	void	*mlx;
	void	*mlx_win;
	void	*s_image;
	int		win_x;
	int		win_y;
	int		bpp;
	int		endian;
	int		size_line;
}	t_mlx;

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}	t_lst;

typedef struct s_verif_map
{
	int		fd;
	char	*line;
	t_lst	*lst;
	int		done;
	char	verif_line;
	int		i;
}	t_verif_map;

typedef struct s_env
{
	t_mlx		mlx;
	t_map		map;
	t_minimap	mini;
	t_calcul	h;
	t_calcul	v;
	t_key		key;
}			t_env;

int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
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

int		get_shading_wall(int red, int green, int blue, double distance_wall);
void	get_RGB(int	color, int *red, int *green, int *blue);
int		c_f_shading(int color, int y);

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
int		set_hooks_mlx(t_env *env);

void	init_pos_l_r(t_pos *pos, t_env *env, int *move);
void	init_pos_t_d(t_pos *pos, t_env *env, int *move);
void	ajust_key_release(int *key1, int *key2);
int		handle_keyrelease(int key_code, t_env *env);
void	ajust_key_press(int *key1, int *key2);
int		handle_keypress(int key_code, t_env *env);
int		handle_key(t_env *env);
void	check_mouse(t_env *env);

void	set_map(t_env *env, int *ptr);
char	*ft_strdup(const char *str);
int		ft_isspace(char c);

void	init_mp_info(t_map *map);

void	ajust_key_release(int *key1, int *key2);
int		handle_keyrelease(int key_code, t_env *env);
void	ajust_key_press(int *key1, int *key2);
int		handle_keypress(int key_code, t_env *env);
void	init_pos_t_d(t_pos *pos, t_env *env, int *move);
void	init_pos_l_r(t_pos *pos, t_env *env, int *move);
double	calcul_angle_l_r(double axe_player, int nb);
int		do_move(double *player, double new_pos);
int		check_collision(t_pos pos, t_env env);

int		atouc(char *nb, int *j);
int		get_color(char *map);
void	line_check_util(char *line, int i, int *j, char *ret);
char	line_check(char *line, int *j);
int		verif_dulicate(char verif_line, t_map *map);
int		check_map(t_map *map);
int		its_player(char c);
int		check_map(t_map *map);
int		check_time(unsigned long long time, unsigned long long intreval);
unsigned long long	ft_get_time();

#endif
