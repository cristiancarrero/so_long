/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_gnl(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, temp);
	}
	free(temp);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen_gnl(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
