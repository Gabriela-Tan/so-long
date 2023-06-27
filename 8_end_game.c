/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_end_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:24:04 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/27 15:23:12 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Free memory for all sprites. */
void	ft_free_sprites(t_master *game)
{
	int	i;
	int no_sprites;

	i = 0;
	no_sprites = 7;
	while (i < no_sprites)
	{
		if (game->sprite[i] != NULL)
		{
			mlx_destroy_image(game->set.mlx, game->sprite[i]->sprite);
			free(game->sprite[i]);
			game->sprite[i] = NULL;
		}
		i++;
	}
}

/* Free memory for the map */
void	ft_free_map(t_master *game)
{
	int row;

	row = 0;
	while (row < game->gta.map_height)
	{
		free(game->gta.map[row]);
		game->gta.map[row] = NULL;
		row++;
	}
	free(game->gta.map);
	game->gta.map = NULL;
}

/* Free memory for the enemy placement. */
void	ft_free_enemy(t_map *gta)
{
	free(gta->enemy_on_col);
	gta->enemy_on_col = NULL;
	free(gta->enemy_on_row);
	gta->enemy_on_row = NULL;
}

/* Free memory for the sprites, map, enemy placement and exits. */
int	ft_clean_up(t_master *game)
{
	if (game != NULL)
	{
		ft_free_sprites(game);
		ft_free_map(game);
		ft_free_enemy(&game->gta);
	}
	exit(0);
}