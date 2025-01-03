/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_count_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

void	update_map_counts(t_game *game, char c, t_count_params p)
{
	if (c == 'P' && ++(*p.player))
	{
		game->player_x = p.j;
		game->player_y = p.i;
	}
	else if (c == 'C')
		game->collectibles++;
	else if (c == 'E')
		++(*p.exit);
}
