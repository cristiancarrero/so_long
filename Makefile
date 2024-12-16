# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = so_long
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
MLX_FLAGS   = -lmlx -lXext -lX11

# Directorios
SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/
LIBFT_DIR   = libft/

# Libft
LIBFT       = $(LIBFT_DIR)libft.a

# Archivos fuente
SRC_FILES   = main.c \
              init.c \
              map.c \
              render.c \
              events.c \
              utils.c

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Reglas
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilando libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpiando objetos..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Limpiando ejecutable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
