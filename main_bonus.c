/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:19:11 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 14:04:19 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_bonus.h"

void	cleanup(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->map_height)
		free(game->map[i++]);
	free(game->map);
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_game	game;

	if (argc != 2)
	{
		write(1, "We need a map as argument 1.\n", 29);
		return (-1);
	}
	if (read_map(&game, argv[1]) == -1)
		return (-1);
	mlx = mlx_init(game.map_width * TILESIZE, (game.map_height + 1) * \
		TILESIZE, "So long, lovers!", 1);
	if (mlx == NULL)
		return (-1);
	game.mlx = mlx;
	if (paint_initial_window(&game) == -1)
		return (-1);
	register_hooks(&game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	cleanup(&game);
}
