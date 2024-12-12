#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

void init_animations(t_game *game)
{
    int width;
    int height;

    printf("%sCargando animaciones...%s\n", CYAN, RESET);
    game->player_anim.frames[0] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player_idle.xpm", &width, &height);
    game->player_anim.frames[1] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player_walk1.xpm", &width, &height);
    game->player_anim.frames[2] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player_walk2.xpm", &width, &height);
    game->player_anim.frames[3] = mlx_xpm_file_to_image(game->mlx, 
        "textures/player_walk3.xpm", &width, &height);

    for (int i = 0; i < ANIMATION_FRAMES; i++)
    {
        if (!game->player_anim.frames[i])
        {
            print_error("Error\nNo se pudieron cargar las animaciones");
            close_window(game);
            return;
        }
    }

    game->player_anim.current_frame = 0;
    game->player_anim.frame_count = ANIMATION_FRAMES;
    game->player_anim.is_moving = 0;
    game->player_anim.direction = 0;
    printf("%sAnimaciones cargadas correctamente%s\n", GREEN, RESET);
}

void update_animation(t_game *game)
{
    static int delay = 0;

    if (game->player_anim.is_moving)
    {
        delay++;
        if (delay >= ANIMATION_SPEED)
        {
            delay = 0;
            game->player_anim.current_frame = 
                (game->player_anim.current_frame + 1) % ANIMATION_FRAMES;
        }
    }
    else
    {
        game->player_anim.current_frame = 0;
        delay = 0;
    }

    render_game(game);
}

void init_enemy_animations(t_game *game)
{
    int width;
    int height;
    int i;

    printf("%sCargando animaciones de enemigos...%s\n", CYAN, RESET);
    
    game->enemy_anim = malloc(sizeof(t_animation) * game->num_enemies);
    
    for (i = 0; i < game->num_enemies; i++)
    {
        game->enemy_anim[i].frames[0] = mlx_xpm_file_to_image(game->mlx,
            "textures/enemy_idle.xpm", &width, &height);
        game->enemy_anim[i].frames[1] = mlx_xpm_file_to_image(game->mlx,
            "textures/enemy_walk1.xpm", &width, &height);
        game->enemy_anim[i].frames[2] = mlx_xpm_file_to_image(game->mlx,
            "textures/enemy_walk2.xpm", &width, &height);
        game->enemy_anim[i].frames[3] = mlx_xpm_file_to_image(game->mlx,
            "textures/enemy_walk3.xpm", &width, &height);

        game->enemy_anim[i].current_frame = 0;
        game->enemy_anim[i].frame_count = ANIMATION_FRAMES;
        game->enemy_anim[i].is_moving = 1;  // Enemigos siempre en movimiento
        game->enemy_anim[i].direction = 0;
        game->enemy_anim[i].frame_delay = 0;
    }
} 