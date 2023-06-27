/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_init_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:56:26 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/24 10:48:39 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Track the placement of enemies in the grid by looping through each row and column. */
void	ft_enemy_placement(t_master *game)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	while (i < game->gta.enemy)
	{
		row = 0;
		while (row < (game->gta.map_height))
		{
			col = 0;
			while (col < (game->gta.map_width))
			{
				if (game->gta.map[row][col] == 'X')
				{
					game->gta.enemy_on_col[i] = col;
					game->gta.enemy_on_row[i] = row;
					i++;
				}
				col++;
			}
			row++;
		}
	}
}

/* Allocate memory for enemy placement */
void	ft_enemy_allocation(t_map *gta)
{
	gta->enemy_on_col = ft_calloc(gta->enemy + 1, (sizeof(int)));
	gta->enemy_on_row = ft_calloc(gta->enemy + 1, (sizeof(int)));
}

/* Tracks the placement of the player by looping through each row and column. */
void	ft_player_placement(t_master *game)
{
	int	row;
	int	col;

	game->player.player_last_row = game->player.player_on_row;
	game->player.player_last_col = game->player.player_on_col;
	row = 0;
	while (row < (game->gta.map_height))
	{
		col = 0;
		while (col < (game->gta.map_width))
		{
			if (game->gta.map[row][col] == 'P')
			{
				game->player.player_on_row = row;
				game->player.player_on_col = col;
			}
			col++;
		}
		row++;
	}
}

/* Initialize variables, save the position of the player and enemies, allocate memory. */
void	ft_game_init(t_master *game)
{
	game->set.img_size = 32;
	game->set.window_width = game->set.img_size
		* game->gta.map_width;
	game->set.window_height = game->set.img_size
		* game->gta.map_height;
	game->player.moves = 0;
	game->player.player_alive = 0;
	game->player.enemy_check = 0;
	game->win = 0;
	ft_player_placement(game);
	ft_enemy_allocation(&game->gta);
	ft_enemy_placement(game);
}
