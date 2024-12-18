void    free_game(t_game *game)
{
    if (!game)
        return;
    
    // ... (código existente)
    free_enemy_textures(game);    // Añade esta línea
    // ... (resto del código)
} 