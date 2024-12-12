#ifndef GAME_H
# define GAME_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"

/* Tamaño de los sprites */
# define TILE_SIZE 64

/* Teclas */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

/* Eventos X11 */
# define KeyPress 2
# define KeyRelease 3
# define ButtonPress 4
# define ButtonRelease 5
# define MotionNotify 6
# define EnterNotify 7
# define LeaveNotify 8
# define FocusIn 9
# define FocusOut 10
# define KeymapNotify 11
# define Expose 12
# define GraphicsExpose 13
# define NoExpose 14

/* Animación */
# define ANIMATION_FRAMES 4
# define ANIMATION_SPEED 10

/* Estructuras */
typedef struct s_position {
    int x;
    int y;
} t_position;

typedef struct s_animation {
    void    *frames[ANIMATION_FRAMES];
    int     current_frame;
    int     frame_count;
    int     is_moving;
    int     direction;  // 0: right, 1: left
    int     frame_delay;  // Nuevo: para controlar la velocidad
} t_animation;

typedef struct s_game {
    void        *mlx;
    void        *win;
    char        **map;
    int         map_width;
    int         map_height;
    void        *img_wall;
    void        *img_floor;
    void        *img_collect;
    void        *img_exit;
    t_animation player_anim;
    int         collectibles;
    int         collected;
    int         moves;
    t_position  player;
    int         anim_frame;
    int         anim_count;
    int         num_enemies;
    t_position  *enemies;    // Array de posiciones de enemigos
    t_animation  *enemy_anim;  // Array de animaciones para enemigos
    int         enemy_move_delay;  // Control de movimiento
} t_game;

/* Funciones */
int     init_game(t_game *game, char *map_path);
int     game_loop(t_game *game);
int     parse_map(t_game *game, char *filename);
int     validate_map(t_game *game);
int     close_window(t_game *game);
int     key_press(int keycode, t_game *game);
int     load_images(t_game *game);
int     render_game(t_game *game);
void    init_animations(t_game *game);
void    update_animation(t_game *game);
void    free_game(t_game *game);
void    print_error(char *message);
void    update_enemies(t_game *game);
int     update_game(t_game *game);
void    move_player(t_game *game, int dx, int dy);

#endif 