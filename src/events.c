#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_window(game);
    else if (keycode == KEY_W || keycode == KEY_UP)
        move_player(game, 0, -1);
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        move_player(game, 0, 1);
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        move_player(game, -1, 0);
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
        move_player(game, 1, 0);

    return (0);
}

int close_window(t_game *game)
{
    if (game)
    {
        if (game->win && game->mlx)
        {
            mlx_destroy_window(game->mlx, game->win);
            game->win = NULL;
        }
        // Aquí deberías liberar todos los recursos
        // free_game(game);
    }
    exit(0);
    return (0);
} 