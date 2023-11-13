/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:28:50 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 18:25:09 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <string.h>
#include <fcntl.h>

void	*read_file(char *file)
{
	int		fd;
	ssize_t	read_bytes;
	char	buffer[MAPSIZE];
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	read_bytes = read(fd, buffer, MAPSIZE - 1);
	if (read_bytes == -1 || read(fd, buffer + read_bytes, 1) != 0)
		return (NULL);
	buffer[read_bytes] = '\0';
	map = ft_split(buffer, '\n');
	if (map == NULL)
		return (NULL);
	else
		return (map);
}

void	get_height(t_game *game)
{
	int		height;
	char	**map;

	map = game->map;
	height = 0;
	while (*map != NULL)
	{
		height++;
		map++;
	}
	game->map_height = height;
}

int	check_all_ones(char *line)
{
	while (*line != '\0')
	{
		if (*line != '1')
			return (0);
		line++;
	}
	return (1);
}

int	check_borders(t_game *game)
{
	int		width;
	int		height;
	char	**map;
	int		i;

	height = game->map_height;
	map = game->map;
	width = ft_strlen(map[0]);
	if (check_all_ones(map[0]) == 0 || check_all_ones(map[height - 1]) == 0)
		return (0);
	i = 1;
	while (i < height - 1)
	{
		if (((int) ft_strlen(map[i])) != width || map[i][0] != '1' || \
			map[i][width - 1] != '1')
			return (0);
		i++;
	}
	game->map_width = width;
	return (1);
}

int	count_pce(t_game *game)
{
	int	p;
	int	e;
	int	i;
	int	j;

	p = 0;
	e = 0;
	game->nr_collectibles = 0;
	i = 1;
	while (i < game->map_height - 1)
	{
		j = 1;
		while (j < game->map_width - 1)
		{
			if (game->map[i][j] == 'P')
				p++;
			if (game->map[i][j] == 'C')
				game->nr_collectibles++;
			if (game->map[i][j] == 'E')
				e++;
			j++;
		}
		i++;
	}
	return (p == 1 && game->nr_collectibles >= 1 && e == 1);
}
