#include "../inc/game.h"
#include "../inc/colors.h"

int update_game(t_game *game)
{
    static int frame_count = 0;

    if (!game || !game->mlx || !game->win)
        return (0);

    frame_count++;
    if (frame_count % 10 == 0)
    {
        game->player_anim.current_frame = (game->player_anim.current_frame + 1) % ANIMATION_FRAMES;
    }

    return (render_game(game));
}

int game_loop(t_game *game)
{
    if (!game || !game->mlx || !game->win)
    {
        printf("%sError: Punteros nulos en game_loop%s\n", RED, RESET);
        return (0);
    }

    printf("\n%sIniciando configuración del bucle de juego...%s\n", CYAN, RESET);
    
    // Configurar hooks con los tipos correctos
    mlx_hook(game->win, 17, 0, &close_window, game);
    mlx_hook(game->win, 2, 1L<<0, &key_press, game);
    mlx_hook(game->win, 12, 1L<<15, &render_game, game);
    mlx_loop_hook(game->mlx, &update_game, game);

    printf("%sRealizando primer renderizado...%s\n", CYAN, RESET);
    if (!render_game(game))
    {
        printf("%sError en el primer renderizado%s\n", RED, RESET);
        return (0);
    }

    printf("%sIniciando bucle principal...%s\n", CYAN, RESET);
    mlx_loop(game->mlx);

    return (1);
} 