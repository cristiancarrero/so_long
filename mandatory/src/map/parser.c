#include "../../inc/game.h"

static int get_map_height(char *filename, char ***map_lines)
{
    int     fd;
    int     height;
    char    *line;
    size_t  len;
    char    **lines;
    int     max_lines;

    height = 0;
    max_lines = 1000;
    lines = ft_calloc(max_lines + 1, sizeof(char *));
    if (!lines)
        return (-1);

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        free(lines);
        return (-1);
    }

    ft_putendl_fd("\nLeyendo altura del mapa:", 1);
    while ((line = get_next_line(fd)))
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        ft_putstr_fd("Línea leída (height): ", 1);
        ft_putendl_fd(line, 1);
        lines[height] = ft_strdup(line);
        height++;
        free(line);
        if (height >= max_lines)
        {
            while (--height >= 0)
                free(lines[height]);
            free(lines);
            close(fd);
            return (-1);
        }
    }
    lines[height] = NULL;
    *map_lines = lines;
    ft_putstr_fd("Altura total: ", 1);
    ft_putnbr_fd(height, 1);
    ft_putchar_fd('\n', 1);
    close(fd);
    return (height);
}

static int get_map_width(char *filename)
{
    int     fd;
    char    *line;
    int     width;
    size_t  len;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);

    ft_putendl_fd("\nLeyendo ancho del mapa:", 1);
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        return (-1);
    }

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    ft_putstr_fd("Primera línea: ", 1);
    ft_putendl_fd(line, 1);

    width = ft_strlen(line);
    ft_putstr_fd("Ancho del mapa: ", 1);
    ft_putnbr_fd(width, 1);
    ft_putchar_fd('\n', 1);

    free(line);
    close(fd);
    return (width);
}

int parse_map(t_game *game, char *filename)
{
	int		i;
	char	**map_lines;

	ft_putendl_fd("\nAbriendo archivo para parsear:", 1);
	ft_putstr_fd("Archivo: ", 1);
	ft_putendl_fd(filename, 1);

	game->map_height = get_map_height(filename, &map_lines);
	if (game->map_height <= 0)
	{
		print_error(ERR_MAP);
		return (0);
	}

	game->map_width = get_map_width(filename);
	if (game->map_width <= 0)
	{
		print_error(ERR_MAP);
		for (i = 0; map_lines[i]; i++)
			free(map_lines[i]);
		free(map_lines);
		return (0);
	}

	ft_putstr_fd("Dimensiones finales del mapa: ", 1);
	ft_putnbr_fd(game->map_width, 1);
	ft_putstr_fd("x", 1);
	ft_putnbr_fd(game->map_height, 1);
	ft_putchar_fd('\n', 1);

	game->map = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map)
	{
		for (i = 0; map_lines[i]; i++)
			free(map_lines[i]);
		free(map_lines);
		return (0);
	}

	ft_putendl_fd("\nCopiando líneas del mapa:", 1);
	for (i = 0; i < game->map_height; i++)
	{
		game->map[i] = ft_strdup(map_lines[i]);
		ft_putstr_fd("Línea ", 1);
		ft_putnbr_fd(i + 1, 1);
		ft_putstr_fd(" (", 1);
		ft_putnbr_fd(ft_strlen(game->map[i]), 1);
		ft_putstr_fd("): ", 1);
		ft_putendl_fd(game->map[i], 1);
	}
	game->map[i] = NULL;

	for (i = 0; map_lines[i]; i++)
		free(map_lines[i]);
	free(map_lines);

	return (1);
}