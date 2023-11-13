/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:49:34 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 13:45:18 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_player(t_game *game, int x, int y)
{
	mlx_image_t	*image;

	image = game->images[3];
	image->instances[0].x += (x - game->player_x) * TILESIZE;
	image->instances[0].y += (y - game->player_y) * TILESIZE;
	game->player_x = x;
	game->player_y = y;
	game->moves += 1;
}

void	move(t_game *game, int x, int y)
{
	size_t	i;

	if (game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'E' && game->points == game->nr_collectibles)
		game->won = 1;
	if (game->map[y][x] == 'C')
	{
		game->map[y][x] = '0';
		i = 0;
		while (i < game->images[4]->count)
		{
			if (game->images[4]->instances[i].x == x * TILESIZE && \
				game->images[4]->instances[i].y == y * TILESIZE)
				game->images[4]->instances[i].enabled = 0;
			i++;
		}
		game->points += 1;
	}
	move_player(game, x, y);
	actualize_byline(game);
	if (game->won)
		print_winner_screen(game);
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
}
