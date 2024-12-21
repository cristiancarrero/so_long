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
	{
		free_game(&game);
		return (1);
	}

	mlx_loop(game.mlx);

	free_game(&game);
	return (0);
} 