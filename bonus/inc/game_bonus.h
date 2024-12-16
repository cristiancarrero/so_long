/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

/* Configuración */
# define TILE_SIZE 64
# define WINDOW_TITLE "so_long"
# define MAX_WINDOW_WIDTH 5000
# define MAX_WINDOW_HEIGHT 5000

/* Variables globales */

/* Caracteres del mapa */
# define EMPTY '0'
# define WALL '1'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECT 'C'
# define ENEMY 'X'

/* Mensajes de error */
# define ERR_ARGS "Error\nUso: ./so_long <mapa.ber>"
# define ERR_MAP "Error\nMapa inválido"
# define ERR_PATH "Error\nNo hay camino válido"
# define ERR_CHARS "Error\nCaracteres inválidos"
# define ERR_RECT "Error\nEl mapa no es rectangular"
# define ERR_WALLS "Error\nMapa no cerrado"
# define ERR_PLAYER "Error\nDebe haber un jugador"
# define ERR_EXIT "Error\nDebe haber una salida"
# define ERR_COLLECT "Error\nDebe haber coleccionables"

/* Teclas */
# define KEY_ESC 65307
# define KEY_W 0x0077
# define KEY_A 0x0061
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113

/* Eventos */
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_EXIT 17
# define X_EVENT_RESIZE 22

/* Máscaras de eventos */
# define KeyPressMask (1L<<0)
# define StructureNotifyMask (1L<<17)
# define NoEventMask 0L

/* Rutas de sprites */
# define SPRITE_PLAYER "./bonus/textures/player.xpm"
# define SPRITE_WALL "./bonus/textures/wall.xpm"
# define SPRITE_FLOOR "./bonus/textures/floor.xpm"
# define SPRITE_COLLECT "./bonus/textures/collect.xpm"
# define SPRITE_EXIT "./bonus/textures/exit.xpm"
# define SPRITE_ENEMY "./bonus/textures/enemy.xpm"

/* Configuración de animaciones */
# define ANIM_DELAY 100    // Delay entre frames en milisegundos
# define PLAYER_FRAMES 4   // Número de frames para la animación del jugador
# define COLLECT_FRAMES 4  // Número de frames para la animación de coleccionables

/* Niveles */
# define MAX_LEVELS 3
# define LEVEL1_PATH "maps/map1.ber"
# define LEVEL2_PATH "maps/map2.ber"
# define LEVEL3_PATH "maps/map3.ber"

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_animation {
    void    **frames;     // Array de imágenes
    int     num_frames;   // Número total de frames
    int     current;      // Frame actual
    int     delay;        // Delay entre frames
    long    last_update;  // Último timestamp
} t_animation;

typedef struct s_particle {
    float   x;
    float   y;
    float   dx;
    float   dy;
    int     life;
    int     color;
} t_particle;

typedef enum e_game_state {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_WIN,
    STATE_LOSE
} t_game_state;

typedef struct s_sound {
    void    *sound;
    char    *path;
    int     volume;
} t_sound;

typedef struct s_enemy
{
	t_position pos;
	int direction;  // 1 para derecha, -1 para izquierda
	int patrol_start;
	int patrol_end;
} t_enemy;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*back_buffer;  // Buffer para doble buffering
	char		**map;
	int			map_width;
	int			map_height;
	int			window_width;
	int			window_height;
	float			scale_x;
	float			scale_y;
	void		*img_wall;
	void		*img_floor;
	void		*img_player;
	void		*img_collect;
	void		*img_exit;
	t_position	player;
	int			collectibles;
	int			collected;
	int			moves;
	int			exit_found;
	int			player_found;
	t_animation  *player_anim;
	t_animation  *collect_anim;
	int         current_level;
	int         max_levels;
	char        **level_paths;
	t_game_state state;
	t_enemy *enemies;
	int     num_enemies;
	void    *img_enemy;
}	t_game;

/* Funciones principales */
int		init_game(t_game *game);
int		load_game(t_game *game, char *map_path);
int		game_loop(void *param);

/* Funciones de mapa */
int		parse_map(t_game *game, char *filename);
int		validate_map(t_game *game);
int		check_path(t_game *game);
char	**copy_map(char **map, int height);

/* Funciones de renderizado */
int		load_images(t_game *game);
int		render_game(t_game *game);
void	render_hud(t_game *game);
void	*scale_image(t_game *game, void *original, float scale);
void	put_image_to_buffer(int *buffer, void *img, int x, int y, int buffer_width, float scale);

/* Funciones de animación */
t_animation	*load_animation(t_game *game, char *base_path, int num_frames);
void		free_animation(t_game *game, t_animation *anim);

/* Funciones de eventos */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
int			window_resize(int width, int height, void *param);
void	move_player(t_game *game, int new_x, int new_y);
void	setup_hooks(t_game *game);

/* Funciones de enemigos */
void	move_enemies(t_game *game);

/* Funciones de utilidad */
void	free_game(t_game *game);
void	print_error(char *message);
void	free_map(char **map);
int		get_time(void);
void	debug_print_images(t_game *game);

#endif