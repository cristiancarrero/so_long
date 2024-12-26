/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	*try_path(const char *base_path, const char *base_name)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(base_path, base_name);
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

const char	*find_texture_path(const char *base_name)
{
	static char	*paths[] = {
		"./textures/bonus/",
		"./textures/bonus/collect/",
		"./textures/bonus/door/",
		"./textures/mandatory/",
		NULL
	};
	char		*result;
	int			i;
	static char	last_path[256];

	i = 0;
	while (paths[i])
	{
		result = try_path(paths[i], base_name);
		if (result)
		{
			ft_strlcpy(last_path, result, sizeof(last_path));
			free(result);
			return (last_path);
		}
		i++;
	}
	return (NULL);
}
