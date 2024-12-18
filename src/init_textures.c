void    init_player_textures(t_game *game)
{
    int width;
    int height;
    
    // Sprite estático
    game->player.idle = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/idle.xpm", &width, &height);
    
    // Animación derecha
    game->player.walk_right[0] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/walk_right1.xpm", &width, &height);
    game->player.walk_right[1] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/walk_right2.xpm", &width, &height);
    game->player.walk_right[2] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/walk_right3.xpm", &width, &height);
    
    // Animación izquierda
    game->player.walk_left[0] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/walk_left1.xpm", &width, &height);
    game->player.walk_left[1] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/walk_left2.xpm", &width, &height);
    game->player.walk_left[2] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player/walk_left3.xpm", &width, &height);
    
    game->player.current = game->player.idle;
    game->player.frame = 0;
    game->player.direction = 0;
    game->player.is_moving = 0;
}

void    init_enemy_textures(t_game *game)
{
    int width;
    int height;
    int i;
    
    for (i = 0; i < game->num_enemies; i++)
    {
        game->enemies[i].sprites[0] = mlx_xpm_file_to_image(game->mlx, 
            "bonus/textures/enemy/enemy1.xpm", &width, &height);
        game->enemies[i].sprites[1] = mlx_xpm_file_to_image(game->mlx, 
            "bonus/textures/enemy/enemy2.xpm", &width, &height);
        game->enemies[i].sprites[2] = mlx_xpm_file_to_image(game->mlx, 
            "bonus/textures/enemy/enemy3.xpm", &width, &height);
        game->enemies[i].current = game->enemies[i].sprites[0];
        game->enemies[i].frame = 0;
        game->enemies[i].active = 1;
    }
}

void    init_door_textures(t_game *game)
{
    int width;
    int height;
    
    game->door.closed = mlx_xpm_file_to_image(game->mlx, 
        "textures/door/door_closed.xpm", &width, &height);
    game->door.open = mlx_xpm_file_to_image(game->mlx, 
        "textures/door/door_open.xpm", &width, &height);
    game->door.current = game->door.closed;
    game->door.is_open = 0;
} 