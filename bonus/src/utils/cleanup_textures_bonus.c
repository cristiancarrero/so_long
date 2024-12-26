/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	cleanup_game_textures(t_game *game)
{
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->collect.img)
		mlx_destroy_image(game->mlx, game->collect.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
}

void	cleanup_player_textures(t_game *game)
{
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
	if (game->player_left.img)
		mlx_destroy_image(game->mlx, game->player_left.img);
}

void	cleanup_enemy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		if (game->enemy[i].img)
			mlx_destroy_image(game->mlx, game->enemy[i].img);
		i++;
	}
}

void	cleanup_buffer_textures(t_game *game)
{
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
	if (game->hud_bg.img)
		mlx_destroy_image(game->mlx, game->hud_bg.img);
}
