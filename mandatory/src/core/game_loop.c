#include "../../inc/game.h"

void    update_game(t_game *game)
{
    if (game->state == STATE_PLAYING)
    {
        animate_player(game);
        animate_enemies(game);
        animate_door(game);
    }
}

int     game_loop(t_game *game)
{
    if (!game || !game->mlx || !game->win)
    {
        printf("%sError: Punteros nulos en game_loop%s\n", RED, RESET);
        return (0);
    }

    printf("\n%sIniciando configuración del bucle de juego...%s\n", CYAN, RESET);

    // Configurar hooks de eventos
    mlx_hook(game->win, 17, 0, &close_window, game);
    mlx_hook(game->win, 2, 1L<<0, &key_press, game);
    mlx_loop_hook(game->mlx, (void *)update_game, game);

    // Iniciar el bucle principal
    mlx_loop(game->mlx);

    return (1);
} 