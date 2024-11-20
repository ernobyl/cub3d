# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 11:34:26 by emichels          #+#    #+#              #
#    Updated: 2024/11/20 20:26:29 by emichels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= cub3d
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX	:= ./MLX42/

HEADERS	:= -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/emichels/.brew/opt/glfw/lib/" -pthread -lm -Llibft -lft
SRCS	:= main.c \
			errors/error_handling.c \
			errors/free_utils.c \
			map_parsing/map_information.c \
			map_parsing/read_map.c \
			map_parsing/valid_map.c \
			map_parsing/map_color_specs.c \
			map_parsing/parsing_utils.c \
			map_parsing/map_wall_checks.c \
			game/minimap.c \
			game/display_images.c \
			game/hook.c \
			game/load_images.c \
			game/raycasting_rays.c \
			game/3d_rendering.c \
			game/texture_to_slice_loops.c \
			game/draw_walls.c \
			game/draw_arrow.c \
			game/defaults.c \
			game/wall_direction.c \
			game/pov_object.c \
			utils/safe_funcs.c \


OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "Compiling cub3d..."
	@make -C libft
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C libft

fclean: clean
	@echo "Cleaning everything else..."
	@rm -rf $(NAME)
	@make fclean -C libft

re: clean all

.PHONY: all, clean, fclean, re, libmlx