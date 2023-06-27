/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_map_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:00:16 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/27 14:45:29 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Initialize used variables */
void	ft_map_init(t_master *game)
{
	game->key = 42;
	game->last_key = 42;
	game->gta.map_width = 0;
	game->gta.map_height = 0;
	game->gta.cash = 0;
	game->gta.player = 0;
	game->gta.exit = 0;
	game->gta.enemy = 0;
}

/* Read the .ber file line by line, character per character,
and store the data in the map array */
void	ft_map_read_content(char *file, t_master *game)
{
	int		fd;
	int		col;
	int		row;
	char	*line;

	row = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_clean_up(game);
	while (row < game->gta.map_height)
	{
		col = 0;
		line = get_next_line(fd);
		while (col < game->gta.map_width)
		{
			game->gta.map[row][col] = line[col];
			col++;
		}
		free(line);
		row++;
	}
	close(fd);
}

/* If memory allocation fails */
void	ft_failed_allocation(t_master *game)
{
	ft_printf("Error! Allocation failed\n");
	ft_clean_up(game);
}

/* Allocate memory for each element of the map. */
int	ft_map_allocation(t_master *game)
{
	int	i;

	i = 0;
	game->gta.map = (char **)ft_calloc(game->gta.map_height, sizeof(char *));
	if (game->gta.map == NULL)
		ft_failed_allocation(game);
	while (i < game->gta.map_height)
	{
		game->gta.map[i] = (char *)ft_calloc(game->gta.map_width + 1, sizeof(char));
		if (game->gta.map[i] == NULL)
			ft_failed_allocation(game);
		i++;
	}
	return (0);
}

/* Read the file */
void	ft_map_set_size(char *file, t_master *game)
{
	char	*line;
	int		fd;

	game->gta.map_height = 1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error! File could not be read.\n");
		exit(0);
	}
	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_printf("Error! File is empty or cannot be read.\n");
		close(fd);
		exit(0);
	}
	game->gta.map_width = ft_strlen(line) - 1;
	free(line);
	while ((line = get_next_line(fd)) != NULL)
	{
		game->gta.map_height++;
		free(line);
	}
	close(fd);
	ft_map_allocation(game);
	ft_map_read_content(file, game);
}
