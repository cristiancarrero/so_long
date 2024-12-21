#include "../../inc/game.h"

void print_error(char *message)
{
    ft_putstr_fd(RED, 2);
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd(RESET, 2);
    ft_putchar_fd('\n', 2);
}

int handle_error(t_game *game, char *message)
{
    print_error(message);
    free_game(game);
    return (0);
} 