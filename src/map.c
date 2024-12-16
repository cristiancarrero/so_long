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

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

static char	*read_line(int fd)
{
	char	*line;
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

static int	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != WALL || 
			game->map[game->map_height - 1][i] != WALL)
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != WALL || 
			game->map[i][game->map_width - 1] != WALL)
			return (0);
		i++;
	}
	return (1);
}

static int	check_chars(t_game *game)
{
	int	i;
	int	j;

	game->collectibles = 0;
	game->player_found = 0;
	game->exit_found = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == PLAYER)
			{
				game->player.x = j;
				game->player.y = i;
				game->player_found++;
			}
			else if (game->map[i][j] == COLLECT)
				game->collectibles++;
			else if (game->map[i][j] == EXIT)
				game->exit_found++;
			else if (game->map[i][j] != WALL && game->map[i][j] != EMPTY)
				return (0);
			j++;
		}
		i++;
	}
	return (game->player_found == 1 && game->exit_found == 1 
		&& game->collectibles > 0);
}

static int	flood_fill(char **map, int x, int y, t_game *game)
{
	static int	collectibles = 0;
	static int	exit = 0;

	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height
		|| map[y][x] == WALL || map[y][x] == 'V')
		return (0);
	if (map[y][x] == COLLECT)
		collectibles++;
	if (map[y][x] == EXIT)
		exit = 1;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
	return (collectibles == game->collectibles && exit);
}

static int	check_rectangular(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (ft_strlen(game->map[i]) != (size_t)game->map_width)
			return (0);
		i++;
	}
	return (1);
}

static void	reset_flood_vars(void)
{
	static int	*collectibles = NULL;
	static int	*exit = NULL;

	if (!collectibles)
		collectibles = &(int){0};
	if (!exit)
		exit = &(int){0};
	*collectibles = 0;
	*exit = 0;
}

int	validate_map(t_game *game)
{
	char	**map_copy;
	int		valid_path;

	if (!check_rectangular(game))
	{
		print_error("Error\nEl mapa no es rectangular");
		return (0);
	}
	if (!check_walls(game))
	{
		print_error(ERR_WALLS);
		return (0);
	}
	if (!check_chars(game))
	{
		print_error(ERR_CHARS);
		return (0);
	}
	map_copy = copy_map(game->map, game->map_height);
	if (!map_copy)
		return (0);
	reset_flood_vars();  // Reseteamos las variables antes del flood fill
	valid_path = flood_fill(map_copy, game->player.x, game->player.y, game);
	free_map(map_copy);
	if (!valid_path)
	{
		print_error(ERR_PATH);
		return (0);
	}
	return (1);
}