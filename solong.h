/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:43:22 by marschul          #+#    #+#             */
/*   Updated: 2023/11/10 18:31:00 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include "MLX42.h"
# include "libft/libft.h"

# include <stdlib.h>
# include <unistd.h>

# define TILESIZE 50
# define MAPSIZE 10001

typedef struct s_game {
	mlx_t			*mlx;
	int				map_width;
	int				map_height;
	char			**map;
	int				player_x;
	int				player_y;
	mlx_image_t		*images[7];
	int				nr_collectibles;
	int				points;
	int				moves;
	int				won;
}	t_game;

int		read_map(t_game *game, char *file);
int		paint_initial_window(t_game *game);
void	register_hooks(t_game *game);
void	*read_file(char *file);
void	get_height(t_game *game);
int		check_borders(t_game *game);
int		count_pce(t_game *game);
void	print_winner_screen(t_game *game);
int		find_exit(char **map, int x, int y);
char	**copy_map(t_game *game);
void	walk_player(t_game *game);
int		set_space(t_game *game, int x, int y);
int		set_wall(t_game *game, int x, int y);
int		set_exit(t_game *game, int x, int y);
int		set_collectible(t_game *game, int x, int y);
int		set_player(t_game *game, int x, int y);
void	actualize_byline(t_game *game);
int		check_superfluous_chars(t_game *game);

#endif