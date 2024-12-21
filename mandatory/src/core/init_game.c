/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

static char	**allocate_map(int height)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = NULL;
	return (map);
}

static int	read_map(char *file_path, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i == 0)
			game->map_width = ft_strlen(line) - 1;
		game->map[i] = ft_strdup(line);
		if (!game->map[i])
		{
			free(line);
			return (0);
		}
		free(line);
		i++;
	}
	close(fd);
	return (1);
}

static int	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_characters(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	game->collectibles = 0;
	game->exit_count = 0;
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (game->map[i][j] == 'P')
			{
				player_count++;
				game->player_pos.x = j;
				game->player_pos.y = i;
			}
			else if (game->map[i][j] == 'C')
				game->collectibles++;
			else if (game->map[i][j] == 'E')
				game->exit_count++;
		}
	}
	return (player_count == 1 && game->collectibles > 0 && game->exit_count == 1);
}

int	validate_map(t_game *game)
{
	int	i;
	int	len;

	if (!game->map || !game->map[0])
		return (0);
	len = ft_strlen(game->map[0]);
	i = 1;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != len)
			return (0);
		i++;
	}
	if (!check_walls(game))
	{
		print_error("El mapa debe estar rodeado de muros");
		return (0);
	}
	if (!check_characters(game))
	{
		print_error("Configuración de caracteres inválida");
		return (0);
	}
	return (1);
}

int	parse_map(char *file_path, t_game *game)
{
	game->map_height = count_lines(file_path);
	if (game->map_height <= 0)
	{
		print_error("No se pudo leer el mapa");
		return (0);
	}
	game->map = allocate_map(game->map_height);
	if (!game->map)
	{
		print_error("No se pudo asignar memoria para el mapa");
		return (0);
	}
	if (!read_map(file_path, game))
	{
		print_error("Error al leer el mapa");
		return (0);
	}
	return (1);
}

void	init_vars(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->moves = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->is_facing_left = 0;  // Inicializando a 0 para que mire a la derecha
}
