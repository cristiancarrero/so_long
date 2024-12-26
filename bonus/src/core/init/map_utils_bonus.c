/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	read_map(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	char	**temp_map;
	int		i;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map_height = 0;
	game->map_width = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	game->map_width = ft_strlen(line) - 1;
	while (line)
	{
		game->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	temp_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!temp_map)
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		free(temp_map);
		return (0);
	}
	i = 0;
	while (i < game->map_height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			while (i > 0)
				free(temp_map[--i]);
			free(temp_map);
			close(fd);
			return (0);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		temp_map[i] = line;
		i++;
	}
	temp_map[i] = NULL;
	game->map = temp_map;
	close(fd);
	return (1);
}
