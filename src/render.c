/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../libft/libft.h"

int	load_images(t_game *game)
{
	int	width;
	int	height;

	ft_putstr_fd("Cargando wall.xpm...\n", 1);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, SPRITE_WALL, &width, &height);
	ft_putstr_fd("Cargando floor.xpm...\n", 1);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, SPRITE_FLOOR, &width, &height);
	ft_putstr_fd("Cargando player.xpm...\n", 1);
	game->img_player = mlx_xpm_file_to_image(game->mlx, SPRITE_PLAYER, &width, &height);
	ft_putstr_fd("Cargando collect.xpm...\n", 1);
	game->img_collect = mlx_xpm_file_to_image(game->mlx, SPRITE_COLLECT, &width, &height);
	ft_putstr_fd("Cargando exit.xpm...\n", 1);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, SPRITE_EXIT, &width, &height);
	
	if (!game->img_wall || !game->img_floor || !game->img_player
		|| !game->img_collect || !game->img_exit)
	{
		ft_putendl_fd("Error al cargar una o más imágenes", 2);
		return (0);
	}
	return (1);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->img_floor, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == WALL)
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == COLLECT)
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_collect, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == EXIT)
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == PLAYER)
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_player, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	render_moves(t_game *game)
{
	char	*moves_str;
	char	*moves_num;

	moves_str = "Moves: ";
	moves_num = ft_itoa(game->moves);
	if (!moves_num)
		return ;
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
	mlx_string_put(game->mlx, game->win, 70, 20, 0xFFFFFF, moves_num);
	free(moves_num);
}
