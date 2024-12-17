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

NAME        = so_long
NAME_BONUS  = so_long_bonus
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
MLX_FLAGS   = -lmlx -lXext -lX11

# Directorios
SRC_DIR     = src/
BONUS_DIR   = bonus/src/
OBJ_DIR     = obj/
OBJ_BONUS_DIR = obj_bonus/
INC_DIR     = inc/
LIBFT_DIR   = libft/

# Libft
LIBFT       = $(LIBFT_DIR)libft.a

# Archivos fuente principales
SRC_FILES   = main.c \
              init.c \
              map.c \
              render.c \
              events.c \
              utils.c

# Archivos bonus
BONUS_FILES = main_bonus.c \
              init_bonus.c \
              map_bonus.c \
              render_bonus.c \
              events_bonus.c \
              game_loop_bonus.c \
              animation_bonus.c \
              utils_bonus.c

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
BONUS_SRCS  = $(addprefix $(BONUS_DIR), $(BONUS_FILES))
OBJS        = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
BONUS_OBJS  = $(addprefix $(OBJ_BONUS_DIR), $(BONUS_FILES:.c=.o))

# Flags de inclusión actualizados para bonus
BONUS_FLAGS = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(BONUS_DIR)/../inc

# Reglas
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilando libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "Compilando so_long..."
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJS)
	@echo "Compilando so_long bonus..."
	$(CC) $(BONUS_OBJS) $(LIBFT) $(MLX_FLAGS) $(BONUS_FLAGS) -o $(NAME_BONUS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)%.o: $(BONUS_DIR)%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) $(BONUS_FLAGS) -c $< -o $@

.bonus: fclean $(LIBFT)
	@echo "Compilando bonus..."
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(MAKE) $(NAME_BONUS)

bonus: .bonus

clean:
	@echo "Limpiando objetos..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@rm -f .bonus
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Limpiando ejecutables..."
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -rf obj_bonus/
	@make -C $(LIBFT_DIR) fclean

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus
