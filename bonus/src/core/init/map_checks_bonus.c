/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

int	check_rectangular(t_game *game)
{
	int		i;
	size_t	expected_len;

	if (game->map_height < 1)
		return (0);
	expected_len = ft_strlen(game->map[0]);
	game->map_width = (int)expected_len;
	i = 1;
	while (i < game->map_height)
	{
		if (ft_strlen(game->map[i]) != expected_len)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1
					|| j == 0 || j == game->map_width - 1)
				&& game->map[i][j] != '1')
				return (0);
		}
	}
	return (1);
}
