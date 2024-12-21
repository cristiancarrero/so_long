void render_hud(t_game *game)
{
    char *moves_str;
    char moves_msg[100];
    char *total_str;
    char total_msg[100];
    int color = 0xFFFFFF;  // Color blanco por defecto

    // Convertir números a strings
    moves_str = ft_itoa(game->moves);
    total_str = ft_itoa(game->collectibles);

    // Crear mensajes
    ft_strlcpy(moves_msg, "Moves: ", sizeof(moves_msg));
    ft_strlcat(moves_msg, moves_str, sizeof(moves_msg));

    ft_strlcpy(total_msg, "Collected: ", sizeof(total_msg));
    ft_strlcat(total_msg, ft_itoa(game->collected), sizeof(total_msg));
    ft_strlcat(total_msg, "/", sizeof(total_msg));
    ft_strlcat(total_msg, total_str, sizeof(total_msg));

    // Renderizar el fondo negro para el HUD
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < game->window_width; x++)
        {
            mlx_pixel_put(game->mlx, game->win, x, y, 0x000000);
        }
    }

    // Renderizar textos
    mlx_string_put(game->mlx, game->win, 10, 20, color, moves_msg);
    mlx_string_put(game->mlx, game->win, 10, 40, color, total_msg);

    // Mostrar mensajes de estado
    if (game->state == STATE_VICTORY)
    {
        mlx_string_put(game->mlx, game->win, 
            (game->window_width / 2) - 100,
            (game->window_height / 2),
            0x00FF00, "¡Has ganado! Presiona ESC para salir");
    }
    else if (game->state == STATE_LOSE)
    {
        mlx_string_put(game->mlx, game->win, 
            (game->window_width / 2) - 100,
            (game->window_height / 2),
            0xFF0000, "¡Has perdido! Presiona ESC para salir");
    }

    // Liberar memoria
    free(moves_str);
    free(total_str);
}

void render_enemies(t_game *game)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].active)
        {
            int pos_x = game->enemies[i].pos.x * TILE_SIZE;
            int pos_y = game->enemies[i].pos.y * TILE_SIZE + 60;  // +60 para el HUD
            
            void *sprite = game->enemies[i].current;
            
            mlx_put_image_to_window(game->mlx, game->win, sprite,
                pos_x, pos_y);
        }
    }
}

void render_game(t_game *game)
{
    // Limpiar la ventana
    mlx_clear_window(game->mlx, game->win);

    // Renderizar el mapa
    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            int pos_x = x * TILE_SIZE;
            int pos_y = y * TILE_SIZE + 60;  // Offset para el HUD

            // Renderizar suelo primero
            mlx_put_image_to_window(game->mlx, game->win, game->img_floor, pos_x, pos_y);

            // Renderizar otros elementos
            if (game->map[y][x] == WALL)
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, pos_x, pos_y);
            else if (game->map[y][x] == COLLECT)
                mlx_put_image_to_window(game->mlx, game->win, game->img_collect, pos_x, pos_y);
            else if (game->map[y][x] == EXIT)
                mlx_put_image_to_window(game->mlx, game->win, game->img_exit, pos_x, pos_y);
        }
    }

    // Renderizar enemigos
    render_enemies(game);

    // Renderizar jugador al final para que siempre esté encima
    int player_x = game->player.x * TILE_SIZE;
    int player_y = game->player.y * TILE_SIZE + 60;
    mlx_put_image_to_window(game->mlx, game->win, game->img_player, player_x, player_y);

    // Renderizar HUD
    render_hud(game);
} 