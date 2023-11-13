/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:34:35 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 14:16:43 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_bonus.h"

int	initialize_enemy(char *file, int index, t_game *game, mlx_t *mlx)
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
	game->enemies[index] = image;
	return (0);
}

int	set_enemy(t_game *game, int x, int y)
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	int			i;

	mlx = game->mlx;
	image = game->images[0];
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	image->instances[image->count - 1].z = 0;
	image = game->enemies[0];
	i = 0;
	while (i < 4)
	{
		if (game->enemies[i]->count == 0)
		{
			image = game->enemies[i];
			break ;
		}
		i++;
	}
	if (mlx_image_to_window(mlx, image, x * TILESIZE, y * TILESIZE) == -1)
		return (-1);
	return (0);
}

void	set_byline(t_game *game)
{
	mlx_t	*mlx;

	mlx = game->mlx;
	game->images[6] = mlx_put_string(mlx, "Smurf Moves : ", TILESIZE, \
		game->map_height * TILESIZE + 0.25 * TILESIZE);
}
