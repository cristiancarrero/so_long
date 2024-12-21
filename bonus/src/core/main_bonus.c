/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	*map_path;

	if (argc != 2)
		return (error_handler(ERR_ARGS));

	map_path = argv[1];
	if (ft_strncmp(map_path, "maps/bonus/", 11) != 0)
		return (error_handler("Error\nDebe usar un mapa del directorio maps/bonus/"));

	printf("Inicializando juego...\n");
	if (!init_game(&game))
		return (1);

	if (!load_game(&game, map_path))
	{
		free_game(&game);
		return (1);
	}

	printf("Iniciando loop principal...\n");
	mlx_loop(game.mlx);
	return (0);
}
