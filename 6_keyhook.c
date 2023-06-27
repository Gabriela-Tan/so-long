/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_keyhook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:02:02 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/25 16:06:58 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Print the number of moves */
void	ft_info_message(t_master *game)
{
	char	*moves;

	moves = ft_itoa(game->player.moves);
	ft_start_message(game);
	mlx_string_put(game->set.mlx, game->set.mlx_win, 10, 10,
		0xFFFFFFFF, "Moves: ");
	mlx_string_put(game->set.mlx, game->set.mlx_win, 55, 10,
		0xFFFFFFFF, moves);
	free(moves);
}

/* Print the right message to the center of the screen once game is over */
void	ft_end_message(t_master *game)
{
	game->player.player_alive++;
	ft_occupy_map(game);
	if (game->gta.cash != 0 || game->player.enemy_check == 42)
		mlx_string_put(game->set.mlx, game->set.mlx_win,
			game->set.window_width / 2 - 20, game->set.window_height / 2, 0xFFFFFFFF, FAIL);
	else
		mlx_string_put(game->set.mlx, game->set.mlx_win,
			game->set.window_width / 2 - 40, game->set.window_height / 2, 0xFFFFFFFF, SUCCESS);
}

/* End the game if the conditions for quitting are met */
int	ft_quit(int keycode, t_master *game)
{
	game->key = keycode;
	if (keycode == 0x35 || keycode == 12)
	{
		mlx_destroy_window(game->set.mlx, game->set.mlx_win);
		ft_clean_up(game);
	}
	if (game->player.player_alive == 0)
	{
		if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
		{
			if (ft_move(game, keycode) == 1)
				ft_end_message(game);
			ft_info_message(game);
		}
	}
	return (0);
}