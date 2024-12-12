#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        print_error(ERR_USAGE);
        return (1);
    }

    printf("%sIniciando juego...%s\n", CYAN, RESET);
    if (!init_game(&game, argv[1]))
    {
        printf("%sError al inicializar el juego%s\n", RED, RESET);
        free_game(&game);
        return (1);
    }

    printf("%sIniciando bucle principal...%s\n", CYAN, RESET);
    if (!game_loop(&game))
    {
        printf("%sError en el bucle principal%s\n", RED, RESET);
        free_game(&game);
        return (1);
    }

    printf("%sLiberando recursos...%s\n", YELLOW, RESET);
    free_game(&game);
    return (0);
} 