int    init_game(t_game *game)
{
    // ... (código existente)
    
    // Añade estas líneas
    init_enemies(game);           // Inicializa la estructura de enemigos
    init_enemy_textures(game);    // Carga las texturas de los enemigos
    
    return (1);
}

void    init_enemies(t_game *game)
{
    int x, y;
    int enemy_count = 0;
    
    // Primero cuenta cuántos enemigos hay
    game->num_enemies = 0;
    for (y = 0; y < game->map_height; y++)
        for (x = 0; x < game->map_width; x++)
            if (game->map[y][x] == 'N')  // Asumiendo que 'N' es el carácter para enemigos
                game->num_enemies++;
    
    // Aloca memoria para los enemigos
    game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
    if (!game->enemies)
        return ;
    
    // Inicializa cada enemigo
    for (y = 0; y < game->map_height; y++)
    {
        for (x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == 'N')
            {
                game->enemies[enemy_count].x = x;
                game->enemies[enemy_count].y = y;
                game->enemies[enemy_count].active = 1;
                enemy_count++;
            }
        }
    }
} 