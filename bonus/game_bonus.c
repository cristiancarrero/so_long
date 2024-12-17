#include "../inc/so_long.h"

// ... resto del código ...

int check_collision(t_game *game, int new_x, int new_y)
{
    // Verificar colisión con enemigos
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (new_x == game->enemy_pos_x[i] && new_y == game->enemy_pos_y[i])
        {
            ft_printf("\n¡Has perdido! Tocaste un enemigo\n");
            close_game(game);
            exit(0);
        }
    }
    return (0);
}

// ... resto del código ... 