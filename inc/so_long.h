#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

# define TILE_SIZE 64
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// Eventos X11
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
# define VisibilityNotify 15
# define CreateNotify 16
# define DestroyNotify 17
# define UnmapNotify 18
# define MapNotify 19
# define MapRequest 20
# define ReparentNotify 21
# define ConfigureNotify 22
# define ConfigureRequest 23
# define GravityNotify 24
# define ResizeRequest 25
# define CirculateNotify 26
# define CirculateRequest 27
# define PropertyNotify 28
# define SelectionClear 29
# define SelectionRequest 30
# define SelectionNotify 31
# define ColormapNotify 32
# define ClientMessage 33
# define MappingNotify 34
# define GenericEvent 35
# define LASTEvent 36

// Máscaras de eventos
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define ButtonPressMask (1L<<2)
# define ButtonReleaseMask (1L<<3)
# define EnterWindowMask (1L<<4)
# define LeaveWindowMask (1L<<5)
# define PointerMotionMask (1L<<6)
# define PointerMotionHintMask (1L<<7)
# define Button1MotionMask (1L<<8)
# define Button2MotionMask (1L<<9)
# define Button3MotionMask (1L<<10)
# define Button4MotionMask (1L<<11)
# define Button5MotionMask (1L<<12)
# define ButtonMotionMask (1L<<13)
# define KeymapStateMask (1L<<14)
# define ExposureMask (1L<<15)
# define VisibilityChangeMask (1L<<16)
# define StructureNotifyMask (1L<<17)
# define ResizeRedirectMask (1L<<18)
# define SubstructureNotifyMask (1L<<19)
# define SubstructureRedirectMask (1L<<20)
# define FocusChangeMask (1L<<21)
# define PropertyChangeMask (1L<<22)
# define ColormapChangeMask (1L<<23)
# define OwnerGrabButtonMask (1L<<24)

# define ANIMATION_FRAMES 4
# define ANIMATION_SPEED 10

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
} t_game;

// Funciones de eventos
int     close_window(t_game *game);
int     key_press(int keycode, t_game *game);

// Funciones principales
int     init_game(t_game *game, char *map_path);
int     game_loop(t_game *game);

// map_parser.c
int     parse_map(t_game *game, char *filename);
int     validate_map(t_game *game);

// game_logic.c
int     handle_key(int keycode, t_game *game);
void    move_player(t_game *game, int new_x, int new_y);

// graphics.c
int     init_graphics(t_game *game);
void    render_map(t_game *game);
int     load_textures(t_game *game);

// utils.c
void    free_game(t_game *game);
void    print_error(char *message);

// render.c
void    load_images(t_game *game);
void    render_game(t_game *game);

// animations.c
void    init_animations(t_game *game);
void    update_animation(t_game *game);

#endif