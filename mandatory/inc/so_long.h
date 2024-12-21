/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		collectibles;
	int		collected;
	int		exit_count;
	int		moves;
	int		is_facing_left;
	t_point	player_pos;
	t_img	floor;
	t_img	wall;
	t_img	player;
	t_img	player_left;
	t_img	collect;
	t_img	exit;
	t_img	buffer;
}	t_game;

// Core functions
void	init_game(t_game *game);
int		load_textures(t_game *game);

// Map functions
int		parse_map(char *file_path, t_game *game);
int		validate_map(t_game *game);

// Event functions
int		handle_keypress(int keycode, t_game *game);
int		handle_window_close(t_game *game);

// Render functions
void	render_map(t_game *game);
int		render_frame(t_game *game);

// Utility functions
void	print_error(char *message);
void	cleanup_game(t_game *game);
void	close_game(t_game *game);

#endif 