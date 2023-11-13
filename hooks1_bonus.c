/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:49:34 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 14:32:12 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_bonus.h"

void	move_player(t_game *game, int x, int y)
{
	game->images[3]->instances[0].x = x * TILESIZE;
	game->images[3]->instances[0].y = y * TILESIZE;
	game->images[7]->instances[0].x = x * TILESIZE;
	game->images[7]->instances[0].y = y * TILESIZE;
	game->images[8]->instances[0].x = x * TILESIZE;
	game->images[8]->instances[0].y = y * TILESIZE;
	game->images[9]->instances[0].x = x * TILESIZE;
	game->images[9]->instances[0].y = y * TILESIZE;
	if ((x < game->player_x && game->player_direction == 0) || \
		(x > game->player_x && game->player_direction == 1))
		switch_player_pictures(game);
	game->player_x = x;
	game->player_y = y;
	game->moves += 1;
}

void	move(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'E' && game->points == game->nr_collectibles)
		game->won = 1;
	if (game->map[y][x] == 'C')
		handle_collectible(game, x, y);
	move_player(game, x, y);
	actualize_byline(game);
	test_if_dead(game);
	if (game->won == 1)
		print_winner_screen(game);
	if (game->won == 2)
		print_loser_screen(game);
}

void	closefunc(void *mlx)
{
	mlx_close_window((mlx_t *) mlx);
}

void	keyfunc(mlx_key_data_t keydata, void *game_)
{
	int		x;
	int		y;
	t_game	*game;

	game = (t_game *) game_;
	x = game->player_x;
	y = game->player_y;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS \
		&& game->won == 0)
		move(game, x, y - 1);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && \
		game->won == 0)
		move(game, x - 1, y);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && \
		game->won == 0)
		move(game, x, y + 1);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && \
		game->won == 0)
		move(game, x + 1, y);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		closefunc(game->mlx);
}

void	register_hooks(t_game *game)
{
	mlx_t	*mlx;

	mlx = game->mlx;
	mlx_key_hook(mlx, keyfunc, game);
	mlx_close_hook(mlx, closefunc, mlx);
	mlx_loop_hook(mlx, move_everybody, game);
}
