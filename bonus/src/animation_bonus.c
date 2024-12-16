#include "../inc/game_bonus.h"

t_animation *load_animation(t_game *game, char *base_path, int num_frames)
{
    t_animation *anim;
    char path[256];
    int i;
    int width;
    int height;

    anim = malloc(sizeof(t_animation));
    if (!anim)
        return (NULL);

    anim->frames = malloc(sizeof(void *) * num_frames);
    if (!anim->frames)
    {
        free(anim);
        return (NULL);
    }

    anim->num_frames = num_frames;
    anim->current = 0;
    anim->delay = ANIM_DELAY;
    anim->last_update = get_time();

    for (i = 0; i < num_frames; i++)
    {
        snprintf(path, sizeof(path), "%s_%d.xpm", base_path, i);
        anim->frames[i] = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
        if (!anim->frames[i])
        {
            // Liberar frames anteriores si hay error
            while (--i >= 0)
                mlx_destroy_image(game->mlx, anim->frames[i]);
            free(anim->frames);
            free(anim);
            return (NULL);
        }
    }
    return (anim);
}

void	free_animation(t_game *game, t_animation *anim)
{
    int i;

    if (!anim)
        return;

    if (anim->frames)
    {
        for (i = 0; i < anim->num_frames; i++)
        {
            if (anim->frames[i])
                mlx_destroy_image(game->mlx, anim->frames[i]);
        }
        free(anim->frames);
    }
    free(anim);
} 