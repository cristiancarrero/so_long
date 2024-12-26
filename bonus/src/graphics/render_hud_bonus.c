/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	render_text(t_game *game, char *moves_msg, char *collect_msg)
{
	mlx_string_put(game->mlx, game->win, 26, 23, 0xFF000000, moves_msg);
	mlx_string_put(game->mlx, game->win, 25, 22, 0xFFFFFFFF, moves_msg);
	mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE - 109,
		23, 0xFF000000, collect_msg);
	mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE - 110,
		22, 0xFFFFFFFF, collect_msg);
}

static void	prepare_moves_msg(t_game *game, char *moves_msg)
{
	char	*moves_str;

	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		return ;
	ft_strlcpy(moves_msg, "Moves: ", 50);
	ft_strlcat(moves_msg, moves_str, 50);
	free(moves_str);
}

static void	prepare_collect_msg(t_game *game, char *collect_msg)
{
	char	*collect_str;
	char	*total_str;

	collect_str = ft_itoa(game->collected);
	if (!collect_str)
		return ;
	ft_strlcpy(collect_msg, "Items: ", 50);
	ft_strlcat(collect_msg, collect_str, 50);
	ft_strlcat(collect_msg, "/", 50);
	free(collect_str);
	total_str = ft_itoa(game->collectibles);
	if (total_str)
	{
		ft_strlcat(collect_msg, total_str, 50);
		free(total_str);
	}
}

void	render_hud(t_game *game)
{
	char	moves_msg[50];
	char	collect_msg[50];

	prepare_moves_msg(game, moves_msg);
	prepare_collect_msg(game, collect_msg);
	render_button_background(game, 5, 7, 120);
	render_button_background(game, game->map_width * TILE_SIZE - 125, 7, 120);
	render_text(game, moves_msg, collect_msg);
}
