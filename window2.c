/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:35:58 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 13:40:33 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	set_space(t_game *game, int x, int y)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = game->mlx;
	image = game->images[0];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	image->instances[image->count - 1].z = 0;
	return (0);
}

int	set_wall(t_game *game, int x, int y)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = game->mlx;
	image = game->images[1];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	else
		return (0);
}

int	set_exit(t_game *game, int x, int y)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = game->mlx;
	image = game->images[2];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	image->instances[image->count - 1].z = 0;
	image = game->images[5];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	image->instances[0].enabled = 0;
	return (0);
}

int	set_collectible(t_game *game, int x, int y)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = game->mlx;
	image = game->images[0];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	image->instances[image->count - 1].z = 0;
	image = game->images[4];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	return (0);
}

int	set_player(t_game *game, int x, int y)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = game->mlx;
	image = game->images[0];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	image->instances[image->count - 1].z = 0;
	image = game->images[3];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	return (0);
}
