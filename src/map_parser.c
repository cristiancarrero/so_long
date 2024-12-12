#include "../inc/game.h"
#include "../inc/map.h"
#include "../inc/colors.h"

static int validate_map_chars(char **map, int height, int width)
{
    int player_count = 0;
    int exit_count = 0;
    int collect_count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char c = map[i][j];
            if (c == 'P')
                player_count++;
            else if (c == 'E')
                exit_count++;
            else if (c == 'C')
                collect_count++;
            else if (c != '0' && c != '1')
                return (0);
        }
    }

    return (player_count == 1 && exit_count == 1 && collect_count > 0);
}

static int validate_map_walls(char **map, int height, int width)
{
    // Verificar primera y última fila
    for (int j = 0; j < width; j++)
    {
        if (map[0][j] != '1' || map[height - 1][j] != '1')
            return (0);
    }

    // Verificar primera y última columna
    for (int i = 0; i < height; i++)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
    }

    return (1);
}

static int count_map_lines(char *map_path)
{
    int     fd;
    int     lines;
    char    *line;

    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return (-1);

    lines = 0;
    while ((line = get_next_line(fd)))
    {
        lines++;
        free(line);
    }

    close(fd);
    return (lines);
}

static char *read_map_line(int fd)
{
    char *line;

    line = get_next_line(fd);
    if (!line)
        return (NULL);

    // Eliminar el salto de línea si existe
    char *newline = ft_strchr(line, '\n');
    if (newline)
        *newline = '\0';

    return (line);
}

int parse_map(t_game *game, char *map_path)
{
    int fd;
    int i;
    char *line;

    printf("Abriendo mapa: %s\n", map_path);
    game->map_height = count_map_lines(map_path);
    if (game->map_height <= 0)
        return (0);

    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return (0);

    game->map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!game->map)
        return (0);

    i = 0;
    game->collectibles = 0;
    while (i < game->map_height)
    {
        line = read_map_line(fd);
        if (!line)
        {
            // Liberar memoria si hay error
            while (i > 0)
                free(game->map[--i]);
            free(game->map);
            close(fd);
            return (0);
        }
        game->map[i] = line;
        i++;
    }
    game->map[i] = NULL;
    close(fd);

    // Validar dimensiones del mapa
    game->map_width = ft_strlen(game->map[0]);
    for (i = 1; i < game->map_height; i++)
    {
        if ((int)ft_strlen(game->map[i]) != game->map_width)
            return (0);
    }

    printf("Validando mapa...\n");
    if (!validate_map_walls(game->map, game->map_height, game->map_width) ||
        !validate_map_chars(game->map, game->map_height, game->map_width))
        return (0);

    // Contar coleccionables y encontrar posición inicial
    for (i = 0; i < game->map_height; i++)
    {
        for (int j = 0; j < game->map_width; j++)
        {
            if (game->map[i][j] == 'C')
                game->collectibles++;
            else if (game->map[i][j] == 'P')
            {
                game->player.x = j;
                game->player.y = i;
                game->map[i][j] = '0';  // Reemplazar P con espacio vacío
            }
        }
    }

    printf("Mapa válido: %dx%d, %d coleccionables\n", 
           game->map_width, game->map_height, game->collectibles);
    printf("Posición inicial del jugador: %d,%d\n", 
           game->player.x, game->player.y);

    return (1);
}