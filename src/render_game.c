void    render_enemies(t_game *game)
{
    int i;
    
    for (i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].active)
        {
            mlx_put_image_to_window(game->mlx, game->win, 
                game->enemies[i].current,
                game->enemies[i].x * TILE_SIZE,
                game->enemies[i].y * TILE_SIZE);
        }
    }
}

int    render_game(t_game *game)
{
    // ... (código existente de renderizado)
    render_map(game);
    render_enemies(game);  // Añade esta línea
    render_player(game);
    // ... (resto del código)
    return (1);
} 