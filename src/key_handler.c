void    handle_movement(t_game *game, int keycode)
{
    game->player.is_moving = 1;
    
    if (keycode == KEY_D || keycode == KEY_RIGHT)
        game->player.direction = 0;
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        game->player.direction = 1;
        
    // Aquí va tu lógica actual de movimiento
}

int    key_release(int keycode, t_game *game)
{
    if (keycode == KEY_A || keycode == KEY_D || 
        keycode == KEY_LEFT || keycode == KEY_RIGHT)
    {
        game->player.is_moving = 0;
    }
    return (0);
} 