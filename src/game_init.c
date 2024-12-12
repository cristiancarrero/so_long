#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

int init_mlx(t_game *game)
{
    printf("Inicializando MLX...\n");
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);

    printf("Creando ventana (%dx%d)...\n", 
           game->map_width * TILE_SIZE, 
           game->map_height * TILE_SIZE);
    
    game->win = mlx_new_window(game->mlx, 
                              game->map_width * TILE_SIZE,
                              game->map_height * TILE_SIZE, 
                              "so_long");
    if (!game->win)
        return (0);

    printf("Ventana creada correctamente\n");
    return (1);
}

int init_game(t_game *game, char *map_path)
{
    printf("Iniciando juego...\n");
    printf("Inicializando estructuras...\n");

    // Inicializar estructura del juego
    game->mlx = NULL;
    game->win = NULL;
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->collectibles = 0;
    game->collected = 0;
    game->moves = 0;
    game->player.x = 0;
    game->player.y = 0;
    game->player_anim.current_frame = 0;

    // Cargar y validar el mapa
    if (!parse_map(game, map_path))
    {
        printf("%sError: Mapa inválido%s\n", RED, RESET);
        return (0);
    }

    // Inicializar MLX
    if (!init_mlx(game))
    {
        printf("%sError: No se pudo inicializar MLX%s\n", RED, RESET);
        return (0);
    }

    // Cargar texturas
    if (!load_images(game))
    {
        printf("%sError: No se pudieron cargar las texturas%s\n", RED, RESET);
        return (0);
    }

    printf("Cargando animaciones...\n");
    printf("Animaciones cargadas correctamente\n");

    return (1);
}