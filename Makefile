# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 19:17:38 by auferran          #+#    #+#              #
#    Updated: 2024/01/29 19:28:24 by madaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
NAME_LEAK = cub3D_leak
CPU_INFO = $(shell cat /proc/cpuinfo  | grep "cpu cores" | uniq | awk '{printf($$4)}')

ifeq ($(CPU_INFO),4)
	SPEED := 6
else
	SPEED := 2
endif

ifeq ($(firstword $(MAKECMDGOALS)),leak)
	LEAK := 1
else
	LEAK := 0
endif

HEADER = cub3D.h
HEADER_BONUS = cub3D_bonus.h

SRCS =	main.c						\
		mlx.c 						\
		key.c						\
		key_util.c					\
		key_utils2.c				\
		utils.c						\
		lst_utils.c					\
		gnl.c						\
		get_map_utils.c				\
		get_map.c					\
		player.c					\
		get_next_wall.c				\
		calcul_wall_h.c				\
		calcul_wall_v.c				\
		calcul_wall_utils.c			\
		calcul_wall_utils_2.c		\
		print_wall.c				\
		minimap/minimap.c			\
		minimap/minimap_utils.c		\
		check_map.c					\
		minimap/display_minimap.c

SRCS_BONUS =	main_bonus.c						\
				mlx_bonus.c 						\
				key_bonus.c							\
				key_util_bonus.c					\
				key_utils2_bonus.c					\
				utils_bonus.c						\
				utils_2_bonus.c						\
				lst_utils_bonus.c					\
				gnl_bonus.c							\
				get_map_utils_bonus.c				\
				get_map_bonus.c						\
				player_bonus.c						\
				get_next_wall_bonus.c				\
				calcul_wall_h_bonus.c				\
				calcul_wall_v_bonus.c				\
				calcul_wall_utils_bonus.c			\
				calcul_wall_utils_2_bonus.c			\
				print_wall_bonus.c					\
				minimap/minimap.c					\
				minimap/minimap_utils.c				\
				check_map_bonus.c					\
				minimap/display_minimap.c			\
				time_bonus.c						\
				manage_mouse_bonus.c				\
				shading_bonus.c

SRCS_LEAK =	main_bonus.c						\
				mlx_bonus.c 						\
				key_bonus.c							\
				key_util_bonus.c					\
				key_utils2_bonus.c					\
				utils_bonus.c						\
				utils_2_bonus.c						\
				lst_utils_bonus.c					\
				gnl_bonus.c							\
				get_map_utils_bonus.c				\
				get_map_bonus.c						\
				player_bonus.c						\
				get_next_wall_bonus.c				\
				calcul_wall_h_bonus.c				\
				calcul_wall_v_bonus.c				\
				calcul_wall_utils_bonus.c			\
				calcul_wall_utils_2_bonus.c			\
				print_wall_bonus.c					\
				minimap/minimap.c					\
				minimap/minimap_utils.c				\
				check_map_bonus.c					\
				minimap/display_minimap.c			\
				time_bonus.c						\
				manage_mouse_bonus.c				\
				shading_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_LEAK = $(SRCS_LEAK:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)

MLX_PATH = ./mlx/
MLX_NAME = libmlx.a
MLX = ${MLX_PATH} ${MLX_NAME}

INC = -I ./mlx_linux/

CC = cc

FLAGS = -Wall -Werror -Wextra -D SPEED=$(SPEED) -D LEAK=$(LEAK) -g -gdwarf-4

$(NAME) : $(OBJS) $(HEADER)
		 make -C ./mlx_linux all
		 $(CC) $(FLAGS) $(OBJS) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -I/usr/include -lXext -lX11 -lm -lz -o $@

$(NAME_BONUS) : $(OBJS_BONUS) $(HEADER_BONUS)
		 make -C ./mlx_linux all
		 $(CC) $(FLAGS) $(OBJS_BONUS) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -I/usr/include -lXext -lX11 -lm -lz -o $@

$(NAME_LEAK) : $(OBJS_LEAK) $(HEADER_BONUS)
		 make -C ./mlx_linux all
		 $(CC) $(OBJS_LEAK) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -I/usr/include -lXext -lX11 -lm -lz -o $@

%.o: %.c
		$(CC) $(FLAGS) -MMD -I/usr/include -Imlx_linux -O3 -c $< -o $@

all : $(NAME)

bonus : $(NAME_BONUS)

leak : $(NAME_LEAK)

clean :
		rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_LEAK) $(DEPS)
		make -C ./mlx_linux clean

fclean : clean
		rm -f $(NAME) $(NAME_BONUS) $(DEPS) $(DEPS_BONUS)

re : fclean all

-include : $(DEPS) $(DEPS_BONUS)

.PHONY: all clean fclean re
