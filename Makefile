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

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus:
	@echo "No bonus part implemented"

.PHONY: all clean fclean re bonus
