# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 19:17:38 by auferran          #+#    #+#              #
#    Updated: 2024/01/30 03:04:05 by madaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
NAME_LEAK = cub3D_leak
SUBD = bonus/
SUBDM = mandatory/
CPU_INFO = $(shell cat /proc/cpuinfo  | grep "cpu cores" | uniq | awk '{printf($$4)}')

ifeq ($(CPU_INFO),4)
	SPEED := 6
else
	SPEED := 2.5
endif

ifeq ($(firstword $(MAKECMDGOALS)),leak)
	LEAK := 1
else
	LEAK := 0
endif

HEADER = mandatory/cub3D.h
HEADER_BONUS = bonus/cub3D_bonus.h

SRCS =	$(SUBDM)main.c						\
		$(SUBDM)free.c						\
		$(SUBDM)img.c						\
		$(SUBDM)mlx.c 						\
		$(SUBDM)key.c						\
		$(SUBDM)key_util.c					\
		$(SUBDM)key_utils2.c				\
		$(SUBDM)utils.c						\
		$(SUBDM)utils_2.c					\
		$(SUBDM)lst_utils.c					\
		$(SUBDM)gnl.c						\
		$(SUBDM)get_map_utils.c				\
		$(SUBDM)get_map.c					\
		$(SUBDM)player.c					\
		$(SUBDM)get_next_wall.c				\
		$(SUBDM)calcul_wall_h.c				\
		$(SUBDM)calcul_wall_v.c				\
		$(SUBDM)calcul_wall_utils.c			\
		$(SUBDM)calcul_wall_utils_2.c		\
		$(SUBDM)print_wall.c				\
		minimap/minimap.c					\
		minimap/minimap_utils.c				\
		minimap/display_minimap.c			\
		$(SUBDM)shading.c					\
		$(SUBDM)check_map.c

SRCS_BONUS =	$(SUBD)main_bonus.c							\
				$(SUBD)mlx_bonus.c 							\
				$(SUBD)key_bonus.c							\
				$(SUBD)key_util_bonus.c						\
				$(SUBD)key_utils2_bonus.c					\
				$(SUBD)utils_bonus.c						\
				$(SUBD)utils_2_bonus.c						\
				$(SUBD)lst_utils_bonus.c					\
				$(SUBD)gnl_bonus.c							\
				$(SUBD)get_map_utils_bonus.c				\
				$(SUBD)get_map_bonus.c						\
				$(SUBD)player_bonus.c						\
				$(SUBD)get_next_wall_bonus.c				\
				$(SUBD)calcul_wall_h_bonus.c				\
				$(SUBD)calcul_wall_v_bonus.c				\
				$(SUBD)calcul_wall_utils_bonus.c			\
				$(SUBD)calcul_wall_utils_2_bonus.c			\
				$(SUBD)print_wall_bonus.c					\
				minimap/minimap.c							\
				minimap/minimap_utils.c						\
				minimap/display_minimap.c					\
				$(SUBD)check_map_bonus.c					\
				$(SUBD)time_bonus.c							\
				$(SUBD)manage_mouse_bonus.c					\
				$(SUBD)shading_bonus.c						\
				$(SUBD)door_bonus.c

SRCS_LEAK =		$(SUBD)main_bonus.c							\
				$(SUBD)mlx_bonus.c 							\
				$(SUBD)key_bonus.c							\
				$(SUBD)key_util_bonus.c						\
				$(SUBD)key_utils2_bonus.c					\
				$(SUBD)utils_bonus.c						\
				$(SUBD)utils_2_bonus.c						\
				$(SUBD)lst_utils_bonus.c					\
				$(SUBD)gnl_bonus.c							\
				$(SUBD)get_map_utils_bonus.c				\
				$(SUBD)get_map_bonus.c						\
				$(SUBD)player_bonus.c						\
				$(SUBD)get_next_wall_bonus.c				\
				$(SUBD)calcul_wall_h_bonus.c				\
				$(SUBD)calcul_wall_v_bonus.c				\
				$(SUBD)calcul_wall_utils_bonus.c			\
				$(SUBD)calcul_wall_utils_2_bonus.c			\
				$(SUBD)print_wall_bonus.c					\
				minimap/minimap.c							\
				minimap/minimap_utils.c						\
				minimap/display_minimap.c					\
				$(SUBD)check_map_bonus.c					\
				$(SUBD)time_bonus.c							\
				$(SUBD)manage_mouse_bonus.c					\
				$(SUBD)shading_bonus.c						\
				$(SUBD)door_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_LEAK = $(SRCS_LEAK:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)

MLX_PATH = ./mlx/
MLX_NAME = libmlx.a
MLX = ${MLX_PATH} ${MLX_NAME}

INC = -I ./mlx_linux/

CC = clang

FLAGS = -Wall -Werror -Wextra -fsanitize=address -D SPEED=$(SPEED) -D LEAK=$(LEAK) -g -gdwarf-4

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
