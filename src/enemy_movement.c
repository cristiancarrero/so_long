#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

static int can_enemy_move(t_game *game, int enemy_index, int new_x, int new_y)
{
    // Verificar límites del mapa
    if (new_x < 0 || new_x >= game->map_width ||
        new_y < 0 || new_y >= game->map_height)
        return (0);

    // Verificar colisiones con paredes
    if (game->map[new_y][new_x] == WALL)
        return (0);

    // Verificar colisiones con otros enemigos
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (i != enemy_index && 
            game->enemies[i].x == new_x && 
            game->enemies[i].y == new_y)
            return (0);
    }

    // Verificar colisión con coleccionables y salida
    if (game->map[new_y][new_x] == COLLECT ||
        game->map[new_y][new_x] == EXIT)
        return (0);

    return (1);
}

void update_enemies(t_game *game)
{
    static int move_delay = 0;
    int i;

    move_delay++;
    if (move_delay < 30)  // Ajusta este valor para cambiar la velocidad
        return;

    move_delay = 0;

    for (i = 0; i < game->num_enemies; i++)
    {
        // Movimiento horizontal
        int new_x = game->enemies[i].x;
        if (game->enemy_anim[i].direction == 0)
            new_x++;
        else
            new_x--;

        // Si puede moverse, actualizar posición
        if (can_enemy_move(game, i, new_x, game->enemies[i].y))
        {
            game->enemies[i].x = new_x;
        }
        else
        {
            // Cambiar dirección si hay colisión
            game->enemy_anim[i].direction = !game->enemy_anim[i].direction;
        }

        // Actualizar animación
        game->enemy_anim[i].frame_delay++;
        if (game->enemy_anim[i].frame_delay >= ANIMATION_SPEED)
        {
            game->enemy_anim[i].frame_delay = 0;
            game->enemy_anim[i].current_frame = 
                (game->enemy_anim[i].current_frame + 1) % ANIMATION_FRAMES;
        }
    }
} 