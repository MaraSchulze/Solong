/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:43 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 14:27:22 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_bonus.h"
#include "libft/libft.h"

void	actualize_byline(t_game *game)
{
	char	str1[100];
	char	*str2;

	str2 = ft_itoa(game->moves);
	ft_strlcpy(str1, "Smurf Moves : ", 20);
	ft_strlcat(str1, str2, 100);
	free(str2);
	mlx_delete_image(game->mlx, game->images[6]);
	game->images[6] = mlx_put_string(game->mlx, str1, TILESIZE, \
		game->map_height * TILESIZE + 0.25 * TILESIZE);
}

void	print_winner_screen(t_game *game)
{
	game->images[2]->instances[0].enabled = 0;
	game->images[3]->instances[0].enabled = 0;
	game->images[7]->instances[0].enabled = 0;
	game->images[5]->instances[0].enabled = 1;
	mlx_put_string(game->mlx, "Schlumpfine forever !!!", game->map_width \
		* TILESIZE - 250, game->map_height * TILESIZE + 0.25 * TILESIZE);
}

void	print_loser_screen(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->enemies[i]->instances[0].x == game->player_x * TILESIZE \
			&& game->enemies[i]->instances[0].y == game->player_y * TILESIZE)
			game->enemies[i]->instances[0].enabled = 0;
		i++;
	}
	game->images[3]->instances[0].enabled = 0;
	game->images[7]->instances[0].enabled = 0;
	mlx_image_to_window(game->mlx, game->images[10], game->player_x * \
		TILESIZE, game->player_y * TILESIZE);
	mlx_put_string(game->mlx, "Loser Smurf !!!", game->map_width * TILESIZE \
		- 250, game->map_height * TILESIZE + 0.25 * TILESIZE);
}

void	walk_player(t_game *game)
{
	mlx_image_t	*image;

	if (game->won == 0 && game->rotator % 30 == 0)
	{
		game->images[3]->instances[0].enabled = 0;
		game->images[7]->instances[0].enabled = 1;
		image = game->images[3];
		game->images[3] = game->images[7];
		game->images[7] = image;
	}
}

void	switch_player_pictures(t_game *game)
{
	mlx_image_t	*image;

	game->images[3]->instances[0].enabled = 0;
	game->images[7]->instances[0].enabled = 0;
	image = game->images[3];
	game->images[3] = game->images[8];
	game->images[8] = image;
	image = game->images[7];
	game->images[7] = game->images[9];
	game->images[9] = image;
	game->player_direction = 1 - game->player_direction;
	game->images[3]->instances[0].enabled = 1;
}
