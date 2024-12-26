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

static int	process_map_line(char *line, char ***map, int i)
{
	char	**temp;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
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
			return (0);
	}
	close(fd);
	game->map_height = i;
	if (i > 0)
		game->map_width = ft_strlen(game->map[0]);
	return (i > 0);
}
