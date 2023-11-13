/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:44:43 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 14:14:38 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_bonus.h"

int	inititialize_image(char *file, int index, t_game *game, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(file);
	if (texture == NULL)
	{
		ft_putstr_fd(mlx_strerror(MLX_INVPNG), 1);
		return (-1);
	}
	texture->width = TILESIZE;
	texture->height = TILESIZE;
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	game->images[index] = image;
	return (0);
}

int	inititialize_images(t_game *game, mlx_t *mlx)
{
	int	error;

	error = 0;
	error += inititialize_image("space.png", 0, game, mlx);
	error += inititialize_image("mushroom.png", 1, game, mlx);
	error += inititialize_image("schlumpfine_50.png", 2, game, mlx);
	error += inititialize_image("smurf_rightfoot.png", 3, game, mlx);
	error += inititialize_image("apple.png", 4, game, mlx);
	error += inititialize_image("kissing.png", 5, game, mlx);
	error += inititialize_image("smurf_leftfoot.png", 7, game, mlx);
	error += inititialize_image("smurf_leftgoing_leftfoot.png", 8, game, mlx);
	error += inititialize_image("smurf_leftgoing_rightfoot.png", 9, game, mlx);
	error += inititialize_image("blacksmurf.png", 10, game, mlx);
	error += initialize_enemy("fish.png", 0, game, mlx);
	error += initialize_enemy("hare.png", 1, game, mlx);
	error += initialize_enemy("hedgehog.png", 2, game, mlx);
	error += initialize_enemy("worm.png", 3, game, mlx);
	return (error);
}

int	paint_tile(t_game *game, int x, int y)
{
	char	c;

	c = game->map[y][x];
	if (c == '0')
		return (set_space(game, x, y));
	if (c == '1')
		return (set_wall(game, x, y));
	if (c == 'E')
		return (set_exit(game, x, y));
	if (c == 'P')
		return (set_player(game, x, y));
	if (c == 'C')
		return (set_collectible(game, x, y));
	if (c == 'X')
		return (set_enemy(game, x, y));
	set_byline(game);
	return (0);
}

int	paint_tiles(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (paint_tile(game, x, y) == -1)
			{
				ft_putstr_fd(mlx_strerror(MLX_INVIMG), 1);
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	paint_initial_window(t_game *game)
{
	mlx_t	*mlx;

	mlx = game->mlx;
	if (inititialize_images(game, mlx) < 0)
		return (-1);
	if (paint_tiles(game) == -1)
		return (-1);
	return (0);
}
