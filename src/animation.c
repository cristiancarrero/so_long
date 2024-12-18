void    animate_player(t_game *game)
{
    static int timer = 0;
    
    if (!game->player.is_moving)
    {
        game->player.current = game->player.idle;
        return;
    }
    
    timer++;
    if (timer >= ANIMATION_SPEED)
    {
        game->player.frame = (game->player.frame + 1) % 3;
        if (game->player.direction == 0)
            game->player.current = game->player.walk_right[game->player.frame];
        else
            game->player.current = game->player.walk_left[game->player.frame];
        timer = 0;
    }
}

void    animate_enemies(t_game *game)
{
    static int timer = 0;
    int i;
    
    timer++;
    if (timer >= ANIMATION_SPEED * 2)
    {
        for (i = 0; i < game->num_enemies; i++)
        {
            if (game->enemies[i].active)
            {
                game->enemies[i].frame = (game->enemies[i].frame + 1) % 3;
                game->enemies[i].current = game->enemies[i].sprites[game->enemies[i].frame];
            }
        }
        timer = 0;
    }
}

void    animate_door(t_game *game)
{
    if (game->collectibles == 0 && !game->door.is_open)
    {
        game->door.current = game->door.open;
        game->door.is_open = 1;
    }
} 