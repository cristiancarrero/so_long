void draw_moves(t_game *game)
{
    char *moves_str;
    
    // Liberar string anterior si existe
    if (game->moves_str)
        free(game->moves_str);
    
    // Crear nuevo string
    moves_str = ft_itoa(game->moves);
    game->moves_str = ft_strjoin("Moves: ", moves_str);
    free(moves_str);
    
    // Dibujar texto en pantalla
    mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, game->moves_str);
} 