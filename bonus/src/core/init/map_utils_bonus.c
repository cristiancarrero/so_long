/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

static int	clean_line(char *line, int len)
{
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
	{
		line[len - 1] = '\0';
		len--;
	}
	return (len);
}

static int	count_lines(char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static int	process_map_line(char *line, char ***map, int i)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	len = clean_line(line, len);
	if (len == 0)
	{
		free(line);
		return (0);
	}
	(*map)[i] = line;
	return (1);
}

static int	handle_map_error(int fd, char **map)
{
	if (fd >= 0)
		close(fd);
	if (map)
		cleanup_map(map);
	return (0);
}

int	read_map(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	game->map_height = count_lines(file_path);
	if (game->map_height <= 0)
		return (0);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (handle_map_error(-1, game->map));
	i = 0;
	while (i < game->map_height)
	{
		line = get_next_line(fd);
		if (!line || !process_map_line(line, &game->map, i))
			return (handle_map_error(fd, game->map));
		i++;
	}
	game->map[i] = NULL;
	close(fd);
	game->map_width = ft_strlen(game->map[0]);
	return (1);
}
