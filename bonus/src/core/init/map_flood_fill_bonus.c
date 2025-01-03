/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height
		|| map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'E')
		return ;
	if (map[y][x] == 'C')
		game->temp_collectibles++;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

static void	flood_fill_exit(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height
		|| map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == 'E')
		game->temp_exit = 1;
	map[y][x] = 'X';
	flood_fill_exit(map, x + 1, y, game);
	flood_fill_exit(map, x - 1, y, game);
	flood_fill_exit(map, x, y + 1, game);
	flood_fill_exit(map, x, y - 1, game);
}

static char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static int	validate_path(t_game *game, char **map1, char **map2)
{
	int	valid;

	game->temp_collectibles = 0;
	game->temp_exit = 0;
	flood_fill(map1, game->player_x, game->player_y, game);
	flood_fill_exit(map2, game->player_x, game->player_y, game);
	valid = (game->temp_collectibles == game->collectibles
			&& game->temp_exit == 1);
	cleanup_map(map1);
	cleanup_map(map2);
	if (!valid)
		ft_putstr_fd("Error: No hay un camino válido\n", 2);
	return (valid);
}

int	check_path(t_game *game)
{
	char	**map_copy;
	char	**map_copy2;

	if (game->player_x < 0 || game->player_y < 0)
	{
		ft_putstr_fd("Error: Posición del jugador inválida\n", 2);
		return (0);
	}
	map_copy = copy_map(game);
	map_copy2 = copy_map(game);
	if (!map_copy || !map_copy2)
	{
		ft_putstr_fd("Error: Fallo en la asignación de memoria\n", 2);
		cleanup_map(map_copy);
		cleanup_map(map_copy2);
		return (0);
	}
	return (validate_path(game, map_copy, map_copy2));
}
