/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:22:37 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 14:33:42 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_bonus.h"
#include "libft/libft.h"

void	move_enemy(t_game *game, int random, int index)
{
	int	i;
	int	x;
	int	y;

	x = game->enemies[index]->instances[0].x / TILESIZE;
	y = game->enemies[index]->instances[0].y / TILESIZE;
	i = 0;
	while (i < 4)
	{
		if (game->map[y - 1][x] == '0' && random-- == 0)
			game->enemies[index]->instances[0].y -= TILESIZE;
		if (game->map[y][x + 1] == '0' && random-- == 0)
			game->enemies[index]->instances[0].x += TILESIZE;
		if (game->map[y + 1][x] == '0' && random-- == 0)
			game->enemies[index]->instances[0].y += TILESIZE;
		if (game->map[y][x - 1] == '0' && random-- == 0)
			game->enemies[index]->instances[0].x -= TILESIZE;
		i++;
	}
}

void	move_enemies(t_game *game)
{
	int	i;
	int	random;

	if (game->rotator % 20 == 0)
	{
		i = 0;
		while (i < 4)
		{
			random = rand() % 4;
			move_enemy(game, random, i);
			i++;
		}
	}
}

void	test_if_dead(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->enemies[i]->instances[0].x / TILESIZE == game->player_x \
			&& game->enemies[i]->instances[0].y / TILESIZE == game->player_y)
		{
			game->won = 2;
			break ;
		}
		i++;
	}
}

void	move_everybody(void *game_)
{
	t_game	*game;

	game = (t_game *) game_;
	game->rotator += 1;
	walk_player(game);
	move_enemies(game);
	test_if_dead(game);
	if (game->won == 2)
		print_loser_screen(game);
}

void	handle_collectible(t_game *game, int x, int y)
{
	size_t	i;

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
