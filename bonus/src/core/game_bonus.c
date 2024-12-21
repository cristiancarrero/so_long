#include "../../inc/game_bonus.h"

// ... resto del código ...

int check_collision(t_game *game, int new_x, int new_y)
{
    // Verificar colisión con enemigos
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (new_x == game->enemies[i].pos.x && new_y == game->enemies[i].pos.y)
        {
            ft_putendl_fd("\n¡Has perdido! Tocaste un enemigo\n", 1);
            close_window(game);
            return (1);
        }
    }
    return (0);
}

// ... resto del código ... 