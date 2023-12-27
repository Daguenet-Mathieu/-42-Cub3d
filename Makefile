# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 19:17:38 by auferran          #+#    #+#              #
#    Updated: 2023/12/14 00:53:56 by madaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_DEBUG = cub3D_debug
NAME_BONUS = cub3D_bonus

HEADER = cub3D.h
HEADER_BONUS = cub3D_bonus.h

SRCS =	main.c					\
		mlx.c 					\
		key.c					\
		utils.c					\
		lst_utils.c				\
		gnl.c					\
		get_map.c				\
		player.c				\
		get_next_wall.c			\
		calcul_wall_h.c			\
		calcul_wall_v.c			\
		calcul_wall_utils.c		\
		calcul_wall_utils_2.c
SRCS_DEBUG =
SRCS_BONUS =

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_DEBUG = $(SRCS_DEBUG:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)

MLX_PATH = ./mlx/
MLX_NAME = libmlx.a
MLX = ${MLX_PATH} ${MLX_NAME}

INC = -I ./mlx_linux/

CC = clang #penser a remetttre cc avant de push

FLAGS = -Wall -Werror -Wextra -g -gdwarf-4

$(NAME) : $(OBJS) $(HEADER)
		 make -C ./mlx_linux all
		 $(CC) $(FLAGS) $(OBJS) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -I/usr/include -lXext -lX11 -lm -lz -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS) $(HEADER_BONUS)
		 make -C ./mlx_linux all
		 $(CC) $(FLAGS) $(OBJS) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -I/usr/include -lXext -lX11 -lm -lz -o $(NAME)

$(NAME_DEBUG) : $(OBJS_DEBUG) $(HEADER)
		 make -C ./mlx_linux all
		 $(CC) $(FLAGS) -fsanitize=address $(OBJS) $(INC) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -MMD -I/usr/include -Imlx_linux -O3 -c $< -o $@

all : $(NAME)

clean :
		rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_DEBUG) $(DEPS)
		make -C ./mlx_linux clean

fclean : clean
		rm -f $(NAME) $(NAME_BONUS) $(NAME_DEBUG) $(DEPS)

re : fclean all

-include : $(DEPS)

.PHONY: all clean fclean re
