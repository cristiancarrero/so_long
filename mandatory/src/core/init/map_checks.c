/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

int	check_rectangular(t_game *game)
{
	int	i;
	int	len;

	len = ft_strlen(game->map[0]);
	i = 0;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_game *game)
{
	int				i;
	int				j;
	int				is_border;
	t_check_params	p;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			p.x = j;
			p.y = i;
			p.width = game->map_width;
			p.height = game->map_height;
			is_border = (p.y == 0 || p.y == p.height - 1
					|| p.x == 0 || p.x == p.width - 1);
			if (is_border && game->map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
