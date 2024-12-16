/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../libft/libft.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	c;
	int		has_char;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	has_char = 0;
	while (read(fd, &c, 1) > 0)
	{
		has_char = 1;
		if (c == '\n')
			lines++;
	}
	if (has_char && c != '\n')
		lines++;
	close(fd);
	return (lines);
}

static char	*read_line(int fd)
{
	char	*line;
	int		len;
	char	c;
	int		i;
	int		bytes;

	line = malloc(1024);
	if (!line)
		return (NULL);
	i = 0;
	while ((bytes = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		line[i++] = c;
		if (i >= 1023)
		{
			free(line);
			return (NULL);
		}
	}
	line[i] = '\0';
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t' || line[len - 1] == '\r'))
		line[--len] = '\0';
	if (bytes <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	parse_map(t_game *game, char *filename)
{
	int		fd;
	int		i;

	game->map_height = count_lines(filename);
	if (game->map_height <= 0)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);

	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
	{
		close(fd);
		return (0);
	}

	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = read_line(fd);
		if (!game->map[i])
		{
			free_map(game->map);
			close(fd);
			return (0);
		}
		if (i == 0)
			game->map_width = ft_strlen(game->map[i]);
		i++;
	}
	game->map[i] = NULL;
	close(fd);
	return (1);
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map)
		return (0);

	// Verificar paredes
	for (i = 0; i < game->map_width; i++)
	{
		if (game->map[0][i] != WALL || game->map[game->map_height - 1][i] != WALL)
			return (0);
	}
	for (i = 0; i < game->map_height; i++)
	{
		if (game->map[i][0] != WALL || game->map[i][game->map_width - 1] != WALL)
			return (0);
	}

	// Inicializar contadores
	game->collectibles = 0;
	game->exit_found = 0;
	game->player_found = 0;

	// Contar elementos y verificar caracteres válidos
	for (i = 0; i < game->map_height; i++)
	{
		for (j = 0; j < game->map_width; j++)
		{
			char c = game->map[i][j];
			if (c == PLAYER)
			{
				if (game->player_found)
					return (0);
				game->player_found = 1;
				game->player.x = j;
				game->player.y = i;
			}
			else if (c == EXIT)
				game->exit_found++;
			else if (c == COLLECT)
				game->collectibles++;
			else if (c != EMPTY && c != WALL)
				return (0);
		}
	}

	// Verificar que hay al menos un jugador, una salida y un coleccionable
	if (!game->player_found || !game->exit_found || !game->collectibles)
		return (0);

	return (1);
}