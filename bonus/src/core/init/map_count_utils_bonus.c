/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_count_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

void	init_counts(t_game *game, t_counts *counts)
{
	counts->player = 0;
	counts->exit = 0;
	game->collectibles = 0;
	game->num_enemies = 0;
}

void	print_char_error(char c)
{
	ft_putstr_fd("Error: Caracter inválido '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("' en el mapa\n", 2);
}

void	print_config_error(int type)
{
	ft_putstr_fd("Error: Configuración inválida - ", 2);
	if (type == 0)
		ft_putstr_fd("Debe haber exactamente un jugador\n", 2);
	else if (type == 1)
		ft_putstr_fd("Debe haber exactamente una salida\n", 2);
	else
		ft_putstr_fd("Debe haber al menos un coleccionable\n", 2);
}
