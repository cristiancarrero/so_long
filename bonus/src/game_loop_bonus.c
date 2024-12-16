/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game_bonus.h"
#include "../libft/libft.h"

int	game_loop(void *param)
{
	ft_putendl_fd("\n=== Iniciando game_loop ===", 1);
	t_game *game;
	
	ft_putendl_fd("Convirtiendo param a game...", 1);
	game = (t_game *)param;
	if (!game || !game->mlx || !game->win)
	{
		ft_putendl_fd("Error: Punteros nulos en game_loop", 2);
		return (0);
	}
	ft_putendl_fd("Verificación de punteros OK", 1);
	
	// Asegurarnos de que el buffer existe
	if (!game->back_buffer)
	{
		ft_putendl_fd("Error: Buffer no inicializado en game_loop", 2);
		return (0);
	}
	
	// Actualizar animaciones si existen
	ft_putendl_fd("Actualizando animaciones...", 1);
	if (game->player_anim)
	{
		static int frame_count = 0;
		frame_count++;
		if (frame_count >= ANIM_DELAY)
		{
			frame_count = 0;
			game->player_anim->current = (game->player_anim->current + 1) % game->player_anim->num_frames;
		}
	}
	ft_putendl_fd("Animaciones actualizadas", 1);
	
	ft_putendl_fd("Renderizando juego...", 1);
	render_game(game);
	ft_putendl_fd("Renderizado completado", 1);
	ft_putendl_fd("=== game_loop completado ===\n", 1);
	
	return (0);
} 