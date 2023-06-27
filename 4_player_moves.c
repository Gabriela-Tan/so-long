/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_player_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:02:20 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/24 16:07:43 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Set player to non-occupied element and set the W/A/S/D
(up, down, left, right) movement */
void	ft_move_player(t_master *game, int row, int col)
{
	game->gta.map[row][col] = '0';
	if (game->key == W && row > 0)
		game->gta.map[row - 1][col] = 'P';
	if (game->key == A && col > 0)
		game->gta.map[row][col - 1] = 'P';
	if (game->key == S && row < game->gta.map_height - 1)
		game->gta.map[row + 1][col] = 'P';
	if (game->key == D && col < game->gta.map_width - 1)
		game->gta.map[row][col + 1] = 'P';
	ft_player_placement(game);
}

/* Check if enemy is located in the spot where the player wants to move.
If so, return 1, if not, return 0 */
int	ft_check_enemy(t_master *game, int row, int col)
{
	if ((row > 0 && game->gta.map[row - 1][col] == 'X' && game->key == W)
	|| (col > 0 && game->gta.map[row][col - 1] == 'X' && game->key == A)
	|| (row < game->gta.map_height - 1 && game->gta.map[row + 1][col] == 'X'
	&& game->key == S)
	|| (col < game->gta.map_width - 1 && game->gta.map[row][col + 1] == 'X'
	&& game->key == D))
	{
		game->player.enemy_check = 42;
		ft_move_player(game, row, col);
		return (1);
	}
	return (0);
}

/* If pressing W/A/S/D (up, down, left, right) leads to exit return 1, 
if not, return 0. */
int	ft_check_exit(t_master *game, int row, int col)
{
	if ((row > 0 && game->gta.map[row - 1][col] == 'E' && game->key == W)
	|| (col > 0 && game->gta.map[row][col - 1] == 'E' && game->key == A)
	|| (row < game->gta.map_height - 1 && game->gta.map[row + 1][col] == 'E'
	&& game->key == S)
	|| (col < game->gta.map_width - 1 && game->gta.map[row][col + 1] == 'E'
	&& game->key == D))
		return (1);
	return (0);
}

/* Check if wall is located in the spot where the player wants to move,
if he'll reach exit or encounter enemy or cash. Move player and enemy. */
int	ft_check_path(t_master *game, int row, int col)
{
	if ((game->gta.map[row - 1][col] != '1' && game->key == W)
	|| (game->gta.map[row][col - 1] != '1' && game->key == A)
	|| (game->gta.map[row + 1][col] != '1' && game->key == S)
	|| (game->gta.map[row][col + 1] != '1' && game->key == D))
	{
		game->player.moves++;
		if (ft_check_exit(game, row, col) == 1)
			return (1);
		if (ft_check_enemy(game, row, col) == 1)
			return (1);
		if ((row > 0 && game->gta.map[row - 1][col] == 'C' && game->key == W)
		|| (col > 0 && game->gta.map[row][col - 1] == 'C' && game->key == A)
		|| (row < game->gta.map_height - 1 && game->gta.map[row + 1][col] == 'C'
		&& game->key == S)
		|| (col < game->gta.map_width - 1 && game->gta.map[row][col + 1] == 'C'
		&& game->key == D))
			game->gta.cash--;
		ft_move_player(game, row, col);
	}
	return (0);
}

/* Update players position based on W/A/S/D (up, down, left, right) keys. 
Check path for exit or enemy (game over) or rebuild the map. */
int	ft_move(t_master *game, int keycode)
{
	int	row;
	int	col;

	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
	{
		game->key = keycode;
		if (game->key == A)
			game->last_key = A;
		if (game->key == D)
			game->last_key = D;
		row = game->player.player_on_row;
		col = game->player.player_on_col;
		if (ft_check_path(game, row, col) == 1)
			return (1);
		ft_occupy_map(game);
	}
	return (0);
}