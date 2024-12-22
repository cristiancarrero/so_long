/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

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

static void	destroy_images(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
	if (game->collect.img)
		mlx_destroy_image(game->mlx, game->collect.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_map(game->map);
	destroy_images(game);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
