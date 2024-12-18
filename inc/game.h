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

# include <mlx.h>
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
# define SPRITE_PLAYER "textures/player.xpm"
# define SPRITE_WALL "textures/wall.xpm"
# define SPRITE_FLOOR "textures/floor.xpm"
# define SPRITE_COLLECT "textures/collect.xpm"
# define SPRITE_EXIT "textures/exit.xpm"

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef enum e_game_state {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_WIN,
    STATE_LOSE
} t_game_state;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*back_buffer;
	char		**map;
	int				map_width;
	int				map_height;
	int				window_width;
	int				window_height;
	float			scale_x;
	float				scale_y;
	void		*img_wall;
	void		*img_floor;
	void		*img_player;
	void		*img_collect;
	void		*img_exit;
	t_position	player;
	int				collectibles;
	int				collected;
	int				moves;
	int				exit_found;
	int				player_found;
	t_game_state	state;
	t_enemy     *enemies;   // Array de enemigos
	int         num_enemies; // Número total de enemigos
}	t_game;

/* Funciones principales */
int		init_game(t_game *game);
int		load_game(t_game *game, char *map_path);
int		game_loop(void *param);

/* Funciones de mapa */
int		parse_map(t_game *game, char *filename);
int		validate_map(t_game *game);
char	**copy_map(char **map, int height);

/* Funciones de renderizado */
int		load_images(t_game *game);
int		render_game(t_game *game);
void	render_hud(t_game *game);
void	*scale_image(t_game *game, void *original, float scale);
void	put_image_to_buffer(int *buffer, void *img, int x, int y, int buffer_width, float scale);
void	*create_buffer(t_game *game);
void	adjust_resolution(t_game *game, int width, int height);

/* Funciones de eventos */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	setup_hooks(t_game *game);

/* Funciones de utilidad */
void	free_game(t_game *game);
void	print_error(char *message);
void	free_map(char **map);
void	debug_print_images(t_game *game);

#define ANIMATION_SPEED 8

typedef struct s_player {
    void    *current;           // Sprite actual
    void    *idle;             // Sprite estático
    void    *walk_right[3];    // Animación derecha
    void    *walk_left[3];     // Animación izquierda
    int     frame;             // Frame actual
    int     x;
    int     y;
    int     is_moving;         // Flag de movimiento
    int     direction;         // 0 = derecha, 1 = izquierda
} t_player;

typedef struct s_enemy {
    void    *sprites[3];    // Cambiado de 2 a 3 para los tres frames
    void    *current;
    int     frame;
    int     x;
    int     y;
    int     active;        // Para saber si el enemigo está activo
} t_enemy;

typedef struct s_door {
    void    *closed;
    void    *open;
    void    *current;
    int     is_open;
    int     x;
    int     y;
} t_door;

typedef struct s_collectible {
    void    *sprites[2];
    void    *current;
    int     frame;
    int     x;
    int     y;
    int     collected;
} t_collectible;

void    init_enemies(t_game *game);
void    init_enemy_textures(t_game *game);
void    animate_enemies(t_game *game);
void    render_enemies(t_game *game);
void    free_enemy_textures(t_game *game);

#endif