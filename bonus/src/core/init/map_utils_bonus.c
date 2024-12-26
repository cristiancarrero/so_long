/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	get_line_length(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

static int	process_line(char *line, t_game *game)
{
	int	len;

	if (!line)
		return (0);
	len = get_line_length(line);
	if (game->map_width == 0)
		game->map_width = len;
	if (len != game->map_width)
	{
		free(line);
		return (0);
	}
	return (1);
}

static char	**allocate_map(t_game *game)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map)
		return (NULL);
	map[game->map_height] = NULL;
	return (map);
}

static int	read_map_lines(int fd, t_game *game, char **map)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->map_height)
	{
		line = get_next_line(fd);
		if (!process_line(line, game))
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (0);
		}
		map[i] = line;
		i++;
	}
	return (1);
}

int	read_map(char *file_path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map_height = 0;
	game->map_width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map_height++;
		free(line);
	}
	close(fd);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map = allocate_map(game);
	if (!game->map || !read_map_lines(fd, game, game->map))
		return (0);
	close(fd);
	return (1);
}
