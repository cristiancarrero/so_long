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

#include "../inc/game_bonus.h"
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

static int	check_walls(t_game *game)
{
	int	i;

	if (game->map_width <= 0 || game->map_height <= 0)
		return (0);

	i = 0;
	while (i < game->map_width)
	{
		if (!game->map[0] || !game->map[game->map_height - 1])
			return (0);
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

static int is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'P' || 
			c == 'E' || c == 'C' || c == 'X' || c == 'N');
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
			if (!is_valid_char(game->map[i][j]))
				return (0);
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
			j++;
		}
		i++;
	}
	return (game->player_found == 1 && game->exit_found == 1 
		&& game->collectibles > 0);
}

typedef struct s_flood {
	int collectibles;
	int exit;
} t_flood;

static void	flood_fill(char **map, int x, int y, t_flood *flood, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height
		|| map[y][x] == WALL || map[y][x] == 'V')
		return;

	if (map[y][x] == COLLECT)
		flood->collectibles++;
	if (map[y][x] == EXIT)
		flood->exit = 1;

	map[y][x] = 'V';
	flood_fill(map, x + 1, y, flood, game);
	flood_fill(map, x - 1, y, flood, game);
	flood_fill(map, x, y + 1, flood, game);
	flood_fill(map, x, y - 1, flood, game);
}

static int check_rectangular(t_game *game)
{
	int i;
	size_t expected_len;

	if (!game->map || !game->map[0])
		return (0);

	// Obtener la longitud esperada de la primera línea
	expected_len = ft_strlen(game->map[0]);
	ft_putstr_fd("Longitud esperada: ", 1);
	ft_putnbr_fd(expected_len, 1);
	ft_putchar_fd('\n', 1);

	i = 1;
	while (i < game->map_height)
	{
		size_t current_len = ft_strlen(game->map[i]);
		ft_putstr_fd("Línea ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" tiene longitud ", 1);
		ft_putnbr_fd(current_len, 1);
		ft_putstr_fd(" (esperada: ", 1);
		ft_putnbr_fd(expected_len, 1);
		ft_putstr_fd(")\n", 1);

		if (current_len != expected_len)
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd("El mapa no es rectangular", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	char	**map_copy;
	t_flood	flood;

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
	flood.collectibles = 0;
	flood.exit = 0;
	flood_fill(map_copy, game->player.x, game->player.y, &flood, game);
	free_map(map_copy);
	if (flood.collectibles != game->collectibles || !flood.exit)
	{
		print_error(ERR_PATH);
		return (0);
	}

	game->num_enemies = 0;
	// Contar enemigos y verificar posiciones
	for (int y = 0; y < game->map_height; y++)
	{
		for (int x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == 'X' || game->map[y][x] == 'N')
				game->num_enemies++;
		}
	}

	// Inicializar array de enemigos
	game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
	if (!game->enemies)
		return (0);

	// Configurar enemigos
	int enemy_index = 0;
	for (int y = 0; y < game->map_height; y++)
	{
		for (int x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == 'X')  // Enemigo tipo 1
			{
				game->enemies[enemy_index].pos.x = x;
				game->enemies[enemy_index].pos.y = y;
				game->enemies[enemy_index].type = 1;
				game->enemies[enemy_index].direction = 1;
				game->enemies[enemy_index].patrol_start = x - 4;
				game->enemies[enemy_index].patrol_end = x + 4;
				game->enemies[enemy_index].active = 1;
				enemy_index++;
			}
			else if (game->map[y][x] == 'N')  // Enemigo tipo 2 (animado)
			{
				game->enemies[enemy_index].pos.x = x;
				game->enemies[enemy_index].pos.y = y;
				game->enemies[enemy_index].type = 2;
				game->enemies[enemy_index].direction = 1;
				game->enemies[enemy_index].patrol_start = x - 3;
				game->enemies[enemy_index].patrol_end = x + 3;
				game->enemies[enemy_index].active = 1;
				enemy_index++;
			}
		}
	}

	return (1);
}