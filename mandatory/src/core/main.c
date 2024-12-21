/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#           */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error(ERR_ARGS);
		return (1);
	}

	ft_memset(&game, 0, sizeof(t_game));

	if (!init_game(&game))
	{
		print_error(ERR_MLX);
		return (1);
	}

	if (!load_game(&game, argv[1]))
	{
		free_game(&game);
		return (1);
	}

	setup_hooks(&game);
	game_loop(&game);

	return (0);
}
