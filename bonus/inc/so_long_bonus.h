/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include "libft.h"
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
# define MAX_ENEMIES 50
# define ENEMY_MOVE_INTERVAL 13
# define ANIMATION_FRAMES 4
# define FRAMES_PER_TYPE 2
# define ANIMATION_SPEED 20

typedef struct s_enemy
{
	int		x;
	int		y;
	int		direction;
	int		frame;
	int		type;
}			t_enemy;

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
	int		collected;
	int		moves;
	int		player_x;
	int		player_y;
	int		is_facing_left;
	int		frame_count;
	int		enemy_move_count;
	int		anim_frame_count;
	int		current_frame;
	int		temp_collectibles;
	int		temp_exit;
	int		temp_enemies;
	t_enemy	enemies[MAX_ENEMIES];
	int		num_enemies;
	t_img	wall;
	t_img	floor;
	t_img	collect;
	t_img	exit;
	t_img	player;
	t_img	player_left;
	t_img	enemy[ANIMATION_FRAMES];
	t_img	buffer;
	t_img	hud_bg;
}			t_game;

typedef struct s_copy_params
{
	t_img	*img;
	int		x;
	int		y;
	int		is_player;
	int		direction;
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

typedef struct s_tile_params
{
	t_game	*game;
	int		i;
	int		x;
	int		y;
	char	tile_type;
}			t_tile_params;

typedef struct s_counts
{
	int	player;
	int	exit;
}	t_counts;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

// Core functions
int			init_mlx(t_game *game);
void		init_img(t_img *img);
int			load_textures(t_game *game);
int			load_player_textures(t_game *game);
int			load_collect_exit_textures(t_game *game);
int			load_wall_floor_textures(t_game *game);

// Graphics functions
void		render_map(t_game *game);
int			render_frame(t_game *game);
void		render_tile(t_game *game, int x, int y);
void		render_floor(t_game *game, int x, int y);
void		render_collectible(t_game *game, int x, int y);
void		copy_image_to_buffer(t_game *game, t_copy_params params);
void		render_hud(t_game *game);
void		render_button_background(t_game *game, int x, int y, int width);

// Image utils
void		destroy_image(void *mlx, t_img *img);

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
void		init_counts(t_game *game, t_counts *counts);
void		print_char_error(char c);
void		print_config_error(int type);

// Cleanup functions
void		cleanup_game(t_game *game);
void		cleanup_map(char **map);
void		cleanup_images(t_game *game);
void		cleanup_game_textures(t_game *game);
void		cleanup_player_textures(t_game *game);
void		cleanup_enemy_textures(t_game *game);
void		cleanup_buffer_textures(t_game *game);

// Error handling
void		print_error(char *message);
void		print_error_and_exit(char *message);

// File reading
char		*get_next_line(int fd);

// Texture utils
const char	*find_texture_path(const char *base_name);

// Game control
void		close_game(t_game *game);

// Enemy functions
void		init_enemies(t_game *game);
void		update_enemies(t_game *game);
int			check_enemy_collision(t_game *game, int x, int y);
void		render_enemies(t_game *game);
void		set_enemy_tile(t_tile_params *params);
void		update_enemy_position(t_game *game, int i, int new_x, int new_y);

// Animation functions
void		update_animation(t_game *game);
int			load_enemy_textures(t_game *game);

// HUD functions
void		init_hud(t_game *game);
void		render_moves_counter(t_game *game);

// Enemy texture utils
void		init_enemy_img(t_img *img);
char		*get_enemy_path(int frame);
int			create_enemy_image(t_game *game, int frame, char *path);

// Enemy path utils
char		*get_enemy_path(int frame);

// Init functions
int			init_game(t_game *game, char *map_path);
void		init_game_values(t_game *game);
void		init_map(t_game *game, char *map_path);
void		init_textures(t_game *game);
void		init_player(t_game *game);

#endif