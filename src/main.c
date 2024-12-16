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

#include "../inc/game.h"
#include "../libft/libft.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error(ERR_ARGS);
		return (1);
	}
	ft_putendl_fd("Iniciando juego...", 1);
	if (!init_game(&game))
	{
		print_error("Error\nFallo en la inicialización");
		return (1);
	}
	ft_putendl_fd("Cargando juego...", 1);
	if (!load_game(&game, argv[1]))
	{
		if (game.mlx)
			free_game(&game);
		return (1);
	}
	ft_putendl_fd("Configurando hooks...", 1);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1L << 0, key_press, &game);
	mlx_hook(game.win, X_EVENT_EXIT, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
