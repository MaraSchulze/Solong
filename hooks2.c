/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:43 by marschul          #+#    #+#             */
/*   Updated: 2023/11/06 21:34:57 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	actualize_byline(t_game *game)
{
	ft_putstr_fd("Moves ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd(", Points ", 1);
	ft_putnbr_fd(game->points, 1);
	ft_putstr_fd("\n", 1);
}

void	print_winner_screen(t_game *game)
{
	game->images[2]->instances[0].enabled = 0;
	game->images[3]->instances[0].enabled = 0;
	game->images[5]->instances[0].enabled = 1;
	ft_putstr_fd("===================================\n", 1);
	ft_putstr_fd("===== Schlumpfine forever !!! =====\n", 1);
	ft_putstr_fd("===================================\n", 1);
}
