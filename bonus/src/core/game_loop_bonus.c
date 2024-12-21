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
	t_game *game;
	static int anim_delay = 0;
	
	game = (t_game *)param;
	if (!game || !game->mlx || !game->win)
		return (0);
	
	// Si el juego ha terminado, no continuar el loop
	if (game->state == STATE_VICTORY || game->state == STATE_LOSE)
		return (0);
	
	// Actualizar animaciones cada 30 frames (aún más lento)
	if (anim_delay >= 30)
	{
		anim_delay = 0;
		for (int i = 0; i < game->num_enemies; i++)
		{
			if (game->enemies[i].active)
			{
				game->enemies[i].frame = (game->enemies[i].frame + 1) % 3;
				game->enemies[i].current = game->enemies[i].sprites[game->enemies[i].frame];
			}
		}
	}
	anim_delay++;
	
	// Mover enemigos
	move_enemies(game);
	
	render_game(game);
	return (0);
} 