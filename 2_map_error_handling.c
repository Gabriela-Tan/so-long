/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_map_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:52:49 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/27 10:56:01 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Check if each border element is 1 to represent a complete wall.
If so, return 0, if not, return 1 */
int	ft_check_border_elements(t_map *gta)
{
	int	col;
	int	row;

	row = 0;
	while (row < (gta->map_height))
	{
		col = 0;
		while (col < (gta->map_width))
		{
			if (row == 0 && gta->map[row][col] != '1')
				return (1);
			if ((row == gta->map_height - 1) && gta->map[row][col] != '1')
				return (1);
			if (col == 0 && gta->map[row][col] != '1')
				return (1);
			if ((col == gta->map_width - 1) && gta->map[row][col] != '1')
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

/* Check if there is 1 player and exit, and at least 1 collectible and enemy
If so, return 0, if not, return 1 */
int	ft_check_valid_characters(t_map *gta)
{
	int	col;
	int	row;

	row = 0;
	while (row < (gta->map_height))
	{
		col = 0;
		while (col < (gta->map_width))
		{
			if (gta->map[row][col] == 'P')
				gta->player++;
			if (gta->map[row][col] == 'E')
				gta->exit++;
			if (gta->map[row][col] == 'C')
				gta->cash++;
			if (gta->map[row][col] == 'X')
				gta->enemy++;
			col++;
		}
		row++;
	}
	if (gta->player != 1 || gta->exit != 1 || gta->cash < 1 || gta->enemy < 1)
		return (1);
	return (0);
}

/* Check if all elements are valid (01PECX)
If so, return 0, if not, return 1 */
int	ft_check_invalid_elements(t_map *gta)
{
	int	col;
	int	row;

	row = 0;
	while (row < (gta->map_height))
	{
		col = 0;
		while (col < (gta->map_width))
		{
			if (gta->map[row][col] != '0' && gta->map[row][col] != '1'
				&& gta->map[row][col] != 'P' && gta->map[row][col] != 'E'
				&& gta->map[row][col] != 'C' && gta->map[row][col] != 'X')
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

/* Return 0 if map is rectangular, has complete outer walls, contains all
needed valid characters and no invalid characters. Print error message and
return 1 if not*/
int	ft_check_map(t_master *game)
{
//	if (game->gta.map_width <= game->gta.map_height)
//	{
//		ft_printf("Error! Map is not rectangular.\n");
//		return (1);
//	}
	if (ft_check_border_elements(&game->gta) == 1)
	{
		ft_printf("Error! Walls are incomplete.\n");
		return (1);
	}
	if (ft_check_valid_characters(&game->gta) == 1)
	{
		ft_printf("Error! Game characters are incomplete.\n");
		return (1);
	}
	if (ft_check_invalid_elements(&game->gta) == 1)
	{
		ft_printf("Error! Some game elements are invalid.\n");
		return (1);
	}
	return (0);
}
