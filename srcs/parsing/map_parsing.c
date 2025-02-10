/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:12:49 by mduvey            #+#    #+#             */
/*   Updated: 2025/02/10 16:56:35 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// does map only contain valid characters 10P

// can we explore the entire map (full fill)

int	is_map_ok(char **map)
{
	if (!is_one_player(map))
		return (ft_printf("parsing error: map should contain 1 player\n"), 0);
	if (!is_map_closed(map))
		return (ft_printf("parsing error: map has to be closed\n"), 0);
	if (!flood_fill(map))
		return (ft_printf("parsing error: every part of \
			the map has to be accessible\n"), 0);
	return (1);
}
