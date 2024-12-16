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

#include "../inc/game_bonus.h"
#include "../libft/libft.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error(ERR_ARGS);
		return (1);
	}

	if (!init_game(&game))
		return (1);

	if (!load_game(&game, argv[1]))
		return (1);

	render_game(&game);

	// Configurar el loop principal
	mlx_hook(game.win, X_EVENT_KEY_PRESS, KeyPressMask, key_press, &game);
	mlx_hook(game.win, X_EVENT_EXIT, NoEventMask, close_window, &game);
	mlx_loop(game.mlx);

	return (0);
}
