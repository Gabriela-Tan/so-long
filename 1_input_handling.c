/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:39:07 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/19 09:18:24 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Return 1 in case of invalid or missing input or return 0 if the input 
is a valid .ber formatted map*/
int	ft_input_handling(int argc, char *argv[])
{
	size_t	len;

	if (argc != 2 || !argv[1])
	{
		ft_printf("Error! Map is invalid.\n");
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error! Map is not in .ber format.\n");
		return (1);
	}
	return (0);
}


/* Call input handling, create map and call functions from MiniLibX. */
int	main(int argc, char *argv[])
{
	t_master	game;

	if (ft_input_handling(argc, argv) == 1)
		exit(0);
	ft_map_init(&game);
	ft_map_set_size(argv[1], &game);
	if (ft_check_map(&game) == 1)
		ft_clean_up(&game);
	game.set.mlx = mlx_init();
	ft_game_init(&game);
	ft_handle_sprites(&game);
	mlx_hook(game.set.mlx_win, 2, 0L, ft_quit, &game);
	mlx_hook(game.set.mlx_win, 17, 1L << 2, ft_clean_up, &game);
	mlx_loop(game.set.mlx);
	return (0);
}