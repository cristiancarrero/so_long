#ifndef MAP_H
# define MAP_H

/* Caracteres válidos en el mapa */
# define VALID_CHARS "01CEPX"
# define PLAYER 'P'
# define COLLECT 'C'
# define EXIT 'E'
# define WALL '1'
# define EMPTY '0'
# define ENEMY 'X'

/* Mensajes de error */
# define ERR_USAGE "Error\nUso: ./so_long [mapa.ber]"
# define ERR_MAP "Error\nMapa inválido"
# define ERR_CHARS "Error\nCaracteres inválidos en el mapa"
# define ERR_WALLS "Error\nEl mapa no está rodeado por muros"
# define ERR_RECT "Error\nEl mapa no es rectangular"
# define ERR_PLAYER "Error\nDebe haber un jugador en el mapa"
# define ERR_EXIT "Error\nDebe haber una salida en el mapa"
# define ERR_COLLECT "Error\nDebe haber al menos un coleccionable"
# define ERR_ENEMY "Error\nDemasiados enemigos en el mapa"

#endif 