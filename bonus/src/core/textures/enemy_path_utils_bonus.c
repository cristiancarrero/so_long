/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_path_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	*get_enemy_type_path(int frame)
{
	if (frame < FRAMES_PER_TYPE)
		return ("./textures/bonus/enemy/enemy");
	return ("./textures/bonus/enemy2/enemy");
}

static char	*create_enemy_filename(int frame)
{
	char	*frame_str;
	char	*temp;
	char	*path;

	frame_str = ft_itoa((frame % FRAMES_PER_TYPE) + 1);
	if (!frame_str)
		return (NULL);
	temp = ft_strjoin(get_enemy_type_path(frame), frame_str);
	free(frame_str);
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, ".xpm");
	free(temp);
	return (path);
}

static int	verify_enemy_path(char *path)
{
	if (!path)
		return (0);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("Error: No se encontró la textura: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

char	*get_enemy_path(int frame)
{
	char	*path;

	path = create_enemy_filename(frame);
	if (!verify_enemy_path(path))
	{
		free(path);
		return (NULL);
	}
	return (path);
}
