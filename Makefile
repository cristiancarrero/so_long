# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by your_login       #+#    #+#             #
#    Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Names
NAME		= so_long
NAME_BONUS	= so_long_bonus
LIBFT		= libft.a

# Directories
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux
OBJ_DIR		= obj

# Compiler and flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
RM			= rm -f

# Mandatory sources
SRCS		= mandatory/src/core/main.c \
			  mandatory/src/core/init.c \
			  mandatory/src/core/cleanup.c \
			  mandatory/src/core/game_loop.c \
			  mandatory/src/map/parser.c \
			  mandatory/src/map/validation.c \
			  mandatory/src/graphics/render.c \
			  mandatory/src/graphics/animations.c \
			  mandatory/src/gameplay/player.c \
			  mandatory/src/utils/error.c \
			  mandatory/src/utils/events.c

# Bonus sources
BONUS_SRCS	= bonus/src/core/main_bonus.c \
			  bonus/src/core/init_bonus.c \
			  bonus/src/core/game_loop_bonus.c \
			  bonus/src/core/cleanup_bonus.c \
			  bonus/src/gameplay/player_bonus.c \
			  bonus/src/graphics/animation_bonus.c \
			  bonus/src/graphics/render_bonus.c \
			  bonus/src/map/map_bonus.c \
			  bonus/src/utils/events_bonus.c \
			  bonus/src/utils/utils_bonus.c

# Objects
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS	= $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(LIBFT_DIR)/$(LIBFT) $(NAME)

bonus: $(LIBFT_DIR)/$(LIBFT) $(NAME_BONUS)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compilando $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)¡$(NAME) compilado!$(RESET)"

$(NAME_BONUS): $(BONUS_OBJS)
	@echo "$(GREEN)Compilando $(NAME_BONUS)...$(RESET)"
	@$(CC) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)¡$(NAME_BONUS) compilado!$(RESET)"

$(LIBFT_DIR)/$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./mandatory/inc -I./bonus/inc -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)Objetos eliminados$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Ejecutables eliminados$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
