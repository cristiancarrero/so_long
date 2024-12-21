/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#           */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <mlx.h>
# include "../../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TILE_SIZE 96
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_TITLE "so_long"

# define SPRITE_WALL "textures/mandatory/wall.xpm"
# define SPRITE_FLOOR "textures/mandatory/floor.xpm"
# define SPRITE_PLAYER "textures/mandatory/player/player.xpm"
# define SPRITE_COLLECT "textures/mandatory/collect/collect.xpm"
# define SPRITE_EXIT "textures/mandatory/door/exit.xpm"

# define STATE_MENU 0
# define STATE_PLAYING 1
# define STATE_PAUSED 2
# define STATE_GAMEOVER 3
# define STATE_LOSE 4
# define STATE_VICTORY 5

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# define ERR_ARGS "Error: Número incorrecto de argumentos"
# define ERR_MAP "Error: No se pudo cargar el mapa"
# define ERR_MLX "Error: No se pudo inicializar MLX"
# define ERR_WIN "Error: No se pudo crear la ventana"
# define ERR_IMG "Error: No se pudieron cargar las imágenes"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_EXIT 17
# define X_EVENT_RESIZE 25

# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define NoEventMask 0L
# define StructureNotifyMask (1L<<17)

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define EMPTY '0'
# define WALL '1'
# define COLLECT 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'N'

typedef struct s_player
{
    int     x;
    int     y;
    void    *sprite_right;
    void    *sprite_left;
    int     direction;
} t_player;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    int     window_width;
    int     window_height;
    void    *img_wall;
    void    *img_floor;
    void    *img_player;
    void    *img_collect;
    void    *img_exit;
    t_player player;
    int     collectibles;
    int     collected;
    int     moves;
    int     state;
    void    *back_buffer;
} t_game;

typedef struct s_img_data
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*orig;
	int		*new;
	unsigned int	color;
}	t_img_data;

// Core functions
int     init_game(t_game *game);
int     load_game(t_game *game, char *map_path);
int     load_images(t_game *game);
void    make_transparent(void *img);
void    debug_print_images(t_game *game);
void    free_game(t_game *game);
void    free_map(char **map);
void    cleanup_game(t_game *game);

// Map functions
int     parse_map(t_game *game, char *map_path);
int     validate_map(t_game *game);

// Graphics functions
int     render_game(t_game *game);
void    *create_transparent_image(void *mlx_ptr, void *src_img);
void    *flip_sprite_horizontally(t_game *game, void *original);
void    *scale_sprite(t_game *game, void *original);
void    render_hud(t_game *game);

// Player functions
void    move_player(t_game *game, int new_x, int new_y);
void    init_player(t_game *game);
int     check_collision(t_game *game, int new_x, int new_y);

// Event functions
void    setup_hooks(t_game *game);
int     key_press(int keycode, t_game *game);
int     close_window(t_game *game);
int     handle_resize(int width, int height, t_game *game);

// Animation functions
void    animate_player(t_game *game);
void    animate_enemies(t_game *game);
void    animate_door(t_game *game);

// Game loop functions
int     game_loop(t_game *game);
void    update_game(t_game *game);

// Get Next Line functions
char    *get_next_line(int fd);
size_t  gnl_strlen(const char *s);
char    *gnl_strchr(const char *s, int c);
char    *gnl_strjoin(char *s1, char *s2);

// Error handling
void    print_error(char *message);

// Debug functions
void    debug_game_state(t_game *game);
void    debug_print_images(t_game *game);

#endif
