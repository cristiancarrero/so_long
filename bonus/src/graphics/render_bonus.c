/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

static void	clear_buffer(t_game *game)
{
	int	i;
	int	size;

	if (!game->buffer.addr)
		return ;
	size = game->buffer.height * game->buffer.line_length;
	i = 0;
	while (i < size)
	{
		game->buffer.addr[i] = 0;
		i++;
	}
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->mlx || !game->win)
	{
		ft_putstr_fd("Error: MLX o ventana no inicializados\n", 1);
		return ;
	}

	if (!game->buffer.img || !game->buffer.addr)
	{
		ft_putstr_fd("Error: Buffer no inicializado\n", 1);
		return ;
	}

	clear_buffer(game);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			render_tile(game, x, y);
		}
	}
	if (game->num_enemies > 0)
		render_enemies(game);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.img, 0, 0);
	render_hud(game);
}

int	render_frame(t_game *game)
{
	render_map(game);
	return (0);
}
