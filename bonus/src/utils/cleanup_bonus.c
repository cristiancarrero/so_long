/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	cleanup_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup_images(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->collect.img)
		mlx_destroy_image(game->mlx, game->collect.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
	if (game->player_left.img)
		mlx_destroy_image(game->mlx, game->player_left.img);
	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		if (game->enemy[i].img)
			mlx_destroy_image(game->mlx, game->enemy[i].img);
		i++;
	}
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
	if (game->hud_bg.img)
		mlx_destroy_image(game->mlx, game->hud_bg.img);
}

void	cleanup_game(t_game *game)
{
	cleanup_images(game);
	cleanup_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
