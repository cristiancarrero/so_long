NAME        = so_long
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -I./inc -I./minilibx-linux -D BUFFER_SIZE=42
MLX_DIR     = minilibx-linux/
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Colores para los mensajes
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

# Directorios
SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/

# Archivos fuente
SRC_FILES   = main.c \
              map_parser.c \
              game_init.c \
              game_loop.c \
              render.c \
              utils.c \
              animations.c \
              events.c \
              enemy_movement.c \
              get_next_line.c \
              get_next_line_utils.c

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS        = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
INCLUDES    = -I$(INC_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compilando MLX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)Compilando $@...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(MLX_FLAGS)
	@echo "$(GREEN)¡Compilación completada!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Limpiando archivos objeto...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Limpiando todo...$(RESET)"
	@rm -f $(NAME)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re