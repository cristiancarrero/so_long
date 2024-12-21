#include "../../inc/game.h"

static int	check_rectangular(char **map)
{
	size_t	len;
	int		i;

	if (!map || !map[0])
		return (0);

	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		char *newline = ft_strchr(map[i], '\n');
		if (newline)
			*newline = '\0';
            
		if (ft_strlen(map[i]) != len)
		{
			ft_putstr_fd("Línea ", 2);
			ft_putnbr_fd(i + 1, 2);
			ft_putstr_fd(" tiene longitud diferente\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_walls(char **map)
{
	int	i;
	int	height;
	int	width;

	if (!map || !map[0])
		return (0);

	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);

	ft_putstr_fd("Altura del mapa: ", 1);
	ft_putnbr_fd(height, 1);
	ft_putchar_fd('\n', 1);

	// Verificar primera y última fila (solo el perímetro)
	if (map[0][0] != WALL || map[0][width - 1] != WALL)
	{
		ft_putendl_fd("Error: Faltan muros en las esquinas de la primera fila", 2);
		return (0);
	}

	if (map[height - 1][0] != WALL || map[height - 1][width - 1] != WALL)
	{
		ft_putendl_fd("Error: Faltan muros en las esquinas de la última fila", 2);
		return (0);
	}

	// Verificar primera y última columna
	for (i = 1; i < height - 1; i++)
	{
		if (map[i][0] != WALL || map[i][width - 1] != WALL)
		{
			ft_putstr_fd("Error en fila ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd(", bordes: '", 2);
			ft_putchar_fd(map[i][0], 2);
			ft_putstr_fd("' y '", 2);
			ft_putchar_fd(map[i][width - 1], 2);
			ft_putendl_fd("'", 2);
			return (0);
		}
	}

	return (1);
}

static int	check_elements(t_game *game)
{
	int	i;
	int	j;
	int	player;
	int	exit;

	player = 0;
	exit = 0;
	game->collectibles = 0;

	ft_putendl_fd("\nVerificando elementos del mapa:", 1);
	ft_putendl_fd("Elementos válidos:", 1);
	ft_putstr_fd("WALL('1'), EMPTY('0'), PLAYER('P'), EXIT('E'), COLLECT('C')", 1);
	if (ENEMY)
		ft_putstr_fd(", ENEMY('N')", 1);
	ft_putchar_fd('\n', 1);

	for (i = 0; i < game->map_height; i++)
	{
		for (j = 0; j < game->map_width; j++)
		{
			ft_putstr_fd("Posición [", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd("][", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd("]: '", 1);
			ft_putchar_fd(game->map[i][j], 1);
			ft_putstr_fd("' ", 1);

			if (game->map[i][j] == PLAYER)
			{
				player++;
				ft_putstr_fd("(PLAYER) ", 1);
			}
			else if (game->map[i][j] == EXIT)
			{
				exit++;
				ft_putstr_fd("(EXIT) ", 1);
			}
			else if (game->map[i][j] == COLLECT)
			{
				game->collectibles++;
				ft_putstr_fd("(COLLECT) ", 1);
			}
			else if (game->map[i][j] == WALL)
				ft_putstr_fd("(WALL) ", 1);
			else if (game->map[i][j] == EMPTY)
				ft_putstr_fd("(EMPTY) ", 1);
			else if (game->map[i][j] == ENEMY)
				ft_putstr_fd("(ENEMY) ", 1);
			else
			{
				ft_putstr_fd("\nCarácter inválido encontrado: '", 2);
				ft_putchar_fd(game->map[i][j], 2);
				ft_putendl_fd("'", 2);
				return (0);
			}
			ft_putchar_fd('\n', 1);
		}
	}

	ft_putstr_fd("\nResumen de elementos encontrados:\n", 1);
	ft_putstr_fd("Jugadores (P): ", 1);
	ft_putnbr_fd(player, 1);
	ft_putstr_fd(" (debe ser 1)\n", 1);
	ft_putstr_fd("Salidas (E): ", 1);
	ft_putnbr_fd(exit, 1);
	ft_putstr_fd(" (debe ser 1)\n", 1);
	ft_putstr_fd("Coleccionables (C): ", 1);
	ft_putnbr_fd(game->collectibles, 1);
	ft_putstr_fd(" (debe ser > 0)\n", 1);

	if (player != 1 || exit != 1 || game->collectibles <= 0)
	{
		ft_putendl_fd("\nError en la cantidad de elementos:", 2);
		if (player != 1)
			ft_putendl_fd("- Número incorrecto de jugadores", 2);
		if (exit != 1)
			ft_putendl_fd("- Número incorrecto de salidas", 2);
		if (game->collectibles <= 0)
			ft_putendl_fd("- No hay suficientes coleccionables", 2);
		return (0);
	}

	return (1);
}

static void	debug_print_map(char **map)
{
	int	i;
	int	j;

	ft_putendl_fd("\nMapa cargado:", 1);
	i = 0;
	while (map[i])
	{
		ft_putstr_fd("Línea ", 1);
		ft_putnbr_fd(i + 1, 1);
		ft_putstr_fd(" (", 1);
		ft_putnbr_fd(ft_strlen(map[i]), 1);
		ft_putstr_fd(" chars): ", 1);
		
		// Imprimir cada carácter con su valor ASCII
		j = 0;
		while (map[i][j])
		{
			ft_putchar_fd(map[i][j], 1);
			j++;
		}
		ft_putstr_fd(" [", 1);
		j = 0;
		while (map[i][j])
		{
			ft_putnbr_fd((int)map[i][j], 1);
			ft_putchar_fd(' ', 1);
			j++;
		}
		ft_putstr_fd("]", 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

int	validate_map(t_game *game)
{
	if (!game || !game->map)
		return (0);

	debug_print_map(game->map);

	if (!check_rectangular(game->map))
	{
		print_error("Error: El mapa no es rectangular");
		return (0);
	}

	if (!check_walls(game->map))
	{
		print_error("Error: El mapa no está rodeado de muros");
		return (0);
	}

	if (!check_elements(game))
	{
		print_error("Error: Elementos del mapa inválidos");
		return (0);
	}

	return (1);
} 