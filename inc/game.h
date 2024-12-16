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
# define KEY_ESC 0xff1b
# define KEY_W 0x0077
# define KEY_A 0x0061
# define KEY_S 0x0073
# define KEY_D 0x0064
# define KEY_Q 0x0071

/* Eventos */
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_EXIT 17

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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
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
}	t_game;

/* Funciones principales */
int		init_game(t_game *game);
int		load_game(t_game *game, char *map_path);
int		game_loop(t_game *game);

/* Funciones de mapa */
int		parse_map(t_game *game, char *filename);
int		validate_map(t_game *game);
int		check_path(t_game *game);
char	**copy_map(char **map, int height);

/* Funciones de renderizado */
int		load_images(t_game *game);
void	render_game(t_game *game);
void	render_moves(t_game *game);

/* Funciones de eventos */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);

/* Funciones de utilidad */
void	free_game(t_game *game);
void	print_error(char *message);
void	free_map(char **map);

#endif