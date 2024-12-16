#include "../inc/game.h"
#include "../libft/libft.h"

void    move_enemies(t_game *game)
{
    if (!game || !game->enemies || game->num_enemies <= 0)
        return;

    static int delay = 0;
    delay++;
    if (delay < 30)
        return;
    delay = 0;

    for (int i = 0; i < game->num_enemies; i++)
    {
        // Guardar posición anterior
        int old_x = game->enemies[i].pos.x;
        
        // Mover enemigo
        game->enemies[i].pos.x += game->enemies[i].direction;
        
        // Comprobar límites de patrulla y colisiones
        if (game->enemies[i].pos.x >= game->enemies[i].patrol_end ||
            game->enemies[i].pos.x <= game->enemies[i].patrol_start ||
            game->map[game->enemies[i].pos.y][game->enemies[i].pos.x] == WALL)
        {
            game->enemies[i].direction *= -1;  // Cambiar dirección
            game->enemies[i].pos.x = old_x;
        }
        
        // Comprobar colisión con jugador
        if (game->enemies[i].pos.x == game->player.x &&
            game->enemies[i].pos.y == game->player.y)
        {
            ft_putendl_fd("\n¡Has muerto! Fin del juego.", 1);
            close_window(game);
            return;
        }
    }
} 