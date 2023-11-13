/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:58:44 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 18:24:39 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	get_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
			}
			j++;
		}
		i++;
	}
}

int	exists_valid_path(t_game *game)
{
	char	**map_copy;
	int		found_exit;
	int		i;

	map_copy = copy_map(game);
	if (map_copy == NULL)
		return (0);
	found_exit = find_exit(map_copy, game->player_x, game->player_y);
	i = 0;
	while (i < game->map_height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (found_exit);
}

int	check_map(t_game *game)
{
	get_height(game);
	if (game->map_height < 3)
		return (-2);
	if (check_borders(game) == 0)
		return (-3);
	if (count_pce(game) == 0)
		return (-4);
	if (check_superfluous_chars(game) == 0)
		return (-4);
	get_player(game);
	if (exists_valid_path(game) == 0)
		return (-5);
	return (0);
}

void	print_error(int error)
{
	write(1, "Error\n", 6);
	if (error == -1)
		write(1, "Error when reading the file.\n", 29);
	if (error == -2)
		write(1, "Map height not >= 3.\n", 21);
	if (error == -3)
		write(1, "Borders not right.\n", 19);
	if (error == -4)
		write(1, "Game figures not right.\n", 24);
	if (error == -5)
		write(1, "There does not exist a valid path.\n", 35);
}

int	read_map(t_game *game, char *file)
{
	int	error;

	game->map = read_file(file);
	if (game->map == NULL)
	{
		print_error(-1);
		return (-1);
	}
	error = check_map(game);
	if (error < 0)
	{
		print_error(error);
		return (-1);
	}
	game->points = 0;
	game->moves = 0;
	game->won = 0;
	return (0);
}
