#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"
#include <string.h>

void print_error(char *message)
{
    write(2, message, strlen(message));
    write(2, "\n", 1);
}

void free_game(t_game *game)
{
    int i;

    if (game->map)
    {
        i = 0;
        while (i < game->map_height)
        {
            if (game->map[i])
                free(game->map[i]);
            i++;
        }
        free(game->map);
    }

    if (game->mlx)
    {
        // Liberar frames de animación
        for (int i = 0; i < ANIMATION_FRAMES; i++)
        {
            if (game->player_anim.frames[i])
                mlx_destroy_image(game->mlx, game->player_anim.frames[i]);
        }

        if (game->img_wall)
            mlx_destroy_image(game->mlx, game->img_wall);
        if (game->img_floor)
            mlx_destroy_image(game->mlx, game->img_floor);
        if (game->img_collect)
            mlx_destroy_image(game->mlx, game->img_collect);
        if (game->img_exit)
            mlx_destroy_image(game->mlx, game->img_exit);
    }

    // Liberar animaciones de enemigos
    if (game->enemy_anim)
    {
        for (int i = 0; i < game->num_enemies; i++)
        {
            for (int j = 0; j < ANIMATION_FRAMES; j++)
            {
                if (game->enemy_anim[i].frames[j])
                    mlx_destroy_image(game->mlx, game->enemy_anim[i].frames[j]);
            }
        }
        free(game->enemy_anim);
    }

    if (game->enemies)
        free(game->enemies);
}

void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player.x + dx;
    int new_y = game->player.y + dy;

    if (new_x < 0 || new_x >= game->map_width || 
        new_y < 0 || new_y >= game->map_height)
        return;

    if (game->map[new_y][new_x] == '1')
        return;

    game->player.x = new_x;
    game->player.y = new_y;
    game->moves++;
    printf("Movimientos: %d\n", game->moves);

    if (game->map[new_y][new_x] == 'C')
    {
        game->map[new_y][new_x] = '0';
        game->collected++;
        printf("Coleccionables: %d/%d\n", game->collected, game->collectibles);
    }

    if (game->map[new_y][new_x] == 'E' && 
        game->collected == game->collectibles)
    {
        printf("\n%s¡Has ganado!%s\n", GREEN, RESET);
        close_window(game);
    }
}

int load_images(t_game *game)
{
    int width, height;

    printf("\n%sCargando texturas...%s\n", CYAN, RESET);

    // Cargar texturas básicas
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &width, &height);
    game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &width, &height);
    game->img_collect = mlx_xpm_file_to_image(game->mlx, "textures/collect.xpm", &width, &height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);

    if (!game->img_wall || !game->img_floor || !game->img_collect || !game->img_exit)
    {
        printf("%sError: No se pudieron cargar las texturas básicas%s\n", RED, RESET);
        return (0);
    }

    // Cargar frames de animación del jugador
    game->player_anim.frames[0] = mlx_xpm_file_to_image(game->mlx, "textures/player_idle.xpm", &width, &height);
    game->player_anim.frames[1] = mlx_xpm_file_to_image(game->mlx, "textures/player_walk1.xpm", &width, &height);
    game->player_anim.frames[2] = mlx_xpm_file_to_image(game->mlx, "textures/player_walk2.xpm", &width, &height);
    game->player_anim.frames[3] = mlx_xpm_file_to_image(game->mlx, "textures/player_walk3.xpm", &width, &height);

    // Verificar que todos los frames se cargaron correctamente
    for (int i = 0; i < ANIMATION_FRAMES; i++)
    {
        if (!game->player_anim.frames[i])
        {
            printf("%sError: No se pudo cargar el frame %d de la animación del jugador%s\n", 
                   RED, i, RESET);
            return (0);
        }
    }

    game->player_anim.current_frame = 0;
    printf("%sTexturas cargadas correctamente%s\n", GREEN, RESET);
    return (1);
}