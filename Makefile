# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f
MLX_FLAGS	= -L./minilibx-linux -lmlx -lXext -lX11 -lm

# Directorios
SRC_DIR		= mandatory/src
OBJ_DIR		= obj
INC_DIR		= mandatory/inc
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# Archivos fuente
SRC_FILES	= main.c \
			  core/init/init_mlx.c \
			  core/init/init_game.c \
			  core/init/map_utils.c \
			  core/init/map_checks.c \
			  core/init/map_validation.c \
			  core/init/map_flood_fill.c \
			  core/init/map_validation_utils.c \
			  core/init_img.c \
			  core/load_textures.c \
			  core/textures/load_player_textures.c \
			  core/textures/load_collect_exit.c \
			  core/textures/load_wall_floor.c \
			  graphics/render.c \
			  graphics/render_tile.c \
			  graphics/render_hud.c \
			  graphics/render_hud_utils.c \
			  graphics/render_utils.c \
			  utils/cleanup.c \
			  utils/events.c \
			  utils/movement.c \
			  utils/error.c \
			  utils/get_next_line.c \
			  utils/get_next_line_utils.c \
			  utils/texture_utils.c \
			  utils/img_utils.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Librerías
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

# Bonus
BONUS_NAME	= so_long_bonus
BONUS_DIR	= bonus/src
BONUS_INC	= bonus/inc

# Archivos que cambian para bonus y archivos base necesarios
BONUS_FILES	= main_bonus.c \
			  core/init_img_bonus.c \
			  core/init/init_game_bonus.c \
			  core/init/init_mlx_bonus.c \
			  core/init/init_game_utils_bonus.c \
			  core/init/map_checks_bonus.c \
			  core/init/map_validation_bonus.c \
			  core/init/map_utils_bonus.c \
			  core/init/map_chars_bonus.c \
			  core/init/map_size_chars_bonus.c \
			  core/init/map_validation_utils_bonus.c \
			  core/init/map_count_utils_bonus.c \
			  core/init/map_flood_fill_bonus.c \
			  core/load_textures_bonus.c \
			  core/textures/load_wall_floor_bonus.c \
			  core/textures/load_player_textures_bonus.c \
			  core/textures/load_collect_exit_bonus.c \
			  core/textures/load_enemy_textures_bonus.c \
			  core/textures/enemy_texture_utils_bonus.c \
			  core/textures/enemy_path_utils_bonus.c \
			  graphics/render_bonus.c \
			  graphics/render_tile_bonus.c \
			  graphics/render_hud_bonus.c \
			  graphics/render_hud_utils_bonus.c \
			  graphics/init_hud_bonus.c \
			  graphics/render_utils_bonus.c \
			  utils/cleanup_bonus.c \
			  utils/cleanup_textures_bonus.c \
			  utils/events_bonus.c \
			  utils/movement_bonus.c \
			  utils/error_bonus.c \
			  utils/get_next_line_bonus.c \
			  utils/get_next_line_utils_bonus.c \
			  utils/texture_utils_bonus.c \
			  utils/img_utils_bonus.c \
			  utils/enemy_bonus.c \
			  utils/enemy_render_bonus.c \
			  utils/enemy_movement_bonus.c \
			  utils/enemy_tile_bonus.c \
			  utils/animation_bonus.c

BONUS_SRCS	= $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
BONUS_OBJS	= $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))

# Include directories
INCLUDES = -Ibonus/inc -Ilibft -Iminilibx-linux

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBFT) $(MLX_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(BONUS_INC) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

clean: clean_bonus
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

clean_bonus:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

fclean_bonus: clean_bonus
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean all

re_bonus: fclean_bonus bonus

bonus: $(LIBFT) $(MLX) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) -o $(BONUS_NAME) $(LIBFT) $(MLX_FLAGS)

.PHONY: all clean fclean re bonus clean_bonus fclean_bonus re_bonus
