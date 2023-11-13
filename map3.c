/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:24:07 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 18:32:41 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	find_exit(char **map, int x, int y)
{
	char	c;
	int		north;
	int		east;
	int		south;
	int		west;

	c = map[y][x];
	if (c == '1' || c == 'x')
		return (0);
	if (c == 'E')
		return (1);
	map[y][x] = 'x';
	north = find_exit(map, x, y - 1);
	east = find_exit(map, x + 1, y);
	south = find_exit(map, x, y + 1);
	west = find_exit(map, x - 1, y);
	return (north || east || south || west);
}

char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;
	int		j;

	map_copy = malloc(game->map_height * sizeof(char *));
	if (map_copy == NULL)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = malloc(game->map_width);
		if (map_copy[i] == NULL)
			return (NULL);
		j = 0;
		while (j < game->map_width)
		{
			map_copy[i][j] = game->map[i][j];
			j++;
		}
		i++;
	}
	return (map_copy);
}

int	check_superfluous_chars(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			c = game->map[i][j];
			if (c != 'P' && c != 'E' && c != 'C' && c != '0' && c != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
