/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

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

static int	process_map_line(char *line, char ***map, int i)
{
	char	**temp;
	int		len;

	len = ft_strlen(line);
	len = clean_line(line, len);
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return (0);
	if (*map)
		ft_memcpy(temp, *map, sizeof(char *) * i);
	temp[i] = line;
	temp[i + 1] = NULL;
	free(*map);
	*map = temp;
	return (1);
}

static int	handle_map_error(int fd, char **map)
{
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

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map = NULL;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_map_line(line, &game->map, i++))
			return (handle_map_error(fd, game->map));
	}
	close(fd);
	game->map_height = i;
	if (i > 0)
		game->map_width = ft_strlen(game->map[0]);
	return (i > 0);
}
