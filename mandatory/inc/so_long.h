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

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64
# define BUFFER_SIZE 1
# define MAX_MAP_WIDTH 50
# define MAX_MAP_HEIGHT 30

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		collectibles;
	int		temp_collectibles;
	int		temp_exit;
	int		exit_found;
	int		collected;
	int		moves;
	int		player_x;
	int		player_y;
	int		is_facing_left;
	t_img	player;
	t_img	wall;
	t_img	floor;
	t_img	collect;
	t_img	exit;
	t_img	buffer;
}			t_game;

typedef struct s_copy_params
{
	t_img	*img;
	int		x;
	int		y;
	int		is_player;
}			t_copy_params;

typedef struct s_check_params
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_check_params;

typedef struct s_count_params
{
	int	*player;
	int	*exit;
	int	i;
	int	j;
}	t_count_params;

// Core functions
int			init_mlx(t_game *game);
void		init_img(t_img *img);
int			init_game(t_game *game, char *map_path);
int			load_textures(t_game *game);
int			load_player_textures(t_game *game);
int			load_collect_textures(t_game *game);
int			load_exit_textures(t_game *game);
int			load_wall_floor_textures(t_game *game);

// Graphics functions
int			render_frame(t_game *game);
void		render_tile(t_game *game, int x, int y);
void		copy_image_to_buffer(t_game *game, t_copy_params params);
void		render_hud(t_game *game);
void		render_button_background(t_game *game, int x, int y, int width);

// Event handling
int			handle_keypress(int keysym, t_game *game);
int			handle_close(t_game *game);
int			move_player(t_game *game, int new_x, int new_y);

// Map validation and loading
int			validate_map(t_game *game);
int			check_path(t_game *game);
int			check_characters(t_game *game);
int			check_walls(t_game *game);
int			check_rectangular(t_game *game);
int			check_map_size_and_chars(t_game *game);
int			read_map(char *file_path, t_game *game);

// Cleanup functions
void		cleanup_game(t_game *game);
void		cleanup_map(char **map);
void		cleanup_images(t_game *game);

// Error handling
void		print_error(char *message);
void		print_error_and_exit(char *message);

// File reading
char		*get_next_line(int fd);

// Texture utils
const char	*find_texture_path(const char *base_name);

void		close_game(t_game *game);

#endif