#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

static void render_tile(t_game *game, void *img, int x, int y)
{
    mlx_put_image_to_window(game->mlx, game->win, img, 
        x * TILE_SIZE, y * TILE_SIZE);
}

int render_game(t_game *game)
{
    if (!game || !game->mlx || !game->win)
    {
        printf("%sError: Punteros nulos en render_game%s\n", RED, RESET);
        return (0);
    }

    // Limpiar ventana
    mlx_clear_window(game->mlx, game->win);

    // Renderizar el mapa
    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            // Renderizar suelo primero
            render_tile(game, game->img_floor, x, y);

            // Renderizar otros elementos
            if (game->map[y][x] == '1')
                render_tile(game, game->img_wall, x, y);
            else if (game->map[y][x] == 'C')
                render_tile(game, game->img_collect, x, y);
            else if (game->map[y][x] == 'E')
                render_tile(game, game->img_exit, x, y);
        }
    }

    // Renderizar jugador
    if (game->player_anim.frames[game->player_anim.current_frame])
    {
        render_tile(game, game->player_anim.frames[game->player_anim.current_frame],
            game->player.x, game->player.y);
    }
    else
    {
        printf("%sError: Frame de animación nulo%s\n", RED, RESET);
        return (0);
    }

    return (1);
} 