# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 11:34:26 by emichels          #+#    #+#              #
#    Updated: 2024/12/03 12:45:23 by emichels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME    := cub3D
CC      := cc
CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast #-g
LIBMLX  := ./MLX42/

HEADERS := -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -Llibft -lft

SHARED_SRCS := errors/error_handling.c \
                errors/free_utils.c \
                map_parsing/map_information.c \
                map_parsing/read_map.c \
                map_parsing/valid_map.c \
                map_parsing/map_color_specs.c \
                map_parsing/parsing_utils.c \
                map_parsing/map_wall_checks.c \
                map_parsing/color_spec_utils.c \
                game/minimap.c \
                game/player_movement.c \
                game/load_images.c \
                game/raycasting_rays.c \
                game/texture_to_slice_loops.c \
                game/draw_walls.c \
                game/defaults.c \
                game/wall_direction.c \
                game/pov_object.c \
                utils/safe_funcs.c \

BASIC_SRCS  := main.c \
                game/hook.c \
                game/draw_arrow.c \
                game/3d_rendering.c \
                game/3d_rendering_draw.c \

BONUS_SRCS  := bonus/main_bonus.c \
                bonus/hook_bonus.c \
                bonus/draw_arrow_bonus.c \
                bonus/3d_rendering_bonus.c \
                bonus/3d_rendering_draw_bonus.c \
                generator_map/map_generator.c \
                generator_map/run_map_gen.c \

SHARED_OBJS := ${SHARED_SRCS:.c=.o}
BASIC_OBJS  := ${BASIC_SRCS:.c=.o}
BONUS_OBJS  := ${BONUS_SRCS:.c=.o}

ifeq ($(BONUS), 1)
OBJS := $(SHARED_OBJS) $(BONUS_OBJS)
else
OBJS := $(SHARED_OBJS) $(BASIC_OBJS)
endif

all: libmlx
	@echo "Switching to basic build..."
	@rm -f $(BONUS_OBJS) $(NAME)
	@$(MAKE) BONUS=0 $(NAME)

bonus: libmlx
	@echo "Building with bonus features..."
	@$(MAKE) BONUS=1 $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@make -C libft
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -f $(SHARED_OBJS) $(BASIC_OBJS) $(BONUS_OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C libft

fclean: clean
	@echo "Cleaning everything else..."
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

rebonus: fclean
	@$(MAKE) BONUS=1 bonus

.PHONY: all clean fclean re libmlx bonus rebonus
