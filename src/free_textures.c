void    free_player_textures(t_game *game)
{
    int i;
    
    if (game->player.idle)
        mlx_destroy_image(game->mlx, game->player.idle);
    for (i = 0; i < 3; i++)
    {
        if (game->player.walk_right[i])
            mlx_destroy_image(game->mlx, game->player.walk_right[i]);
        if (game->player.walk_left[i])
            mlx_destroy_image(game->mlx, game->player.walk_left[i]);
    }
}

void    free_enemy_textures(t_game *game)
{
    int i, j;
    
    for (i = 0; i < game->num_enemies; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (game->enemies[i].sprites[j])
                mlx_destroy_image(game->mlx, game->enemies[i].sprites[j]);
        }
    }
    if (game->enemies)
        free(game->enemies);
} 