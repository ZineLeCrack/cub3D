/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:09 by mduvey            #+#    #+#             */
/*   Updated: 2025/02/10 16:53:50 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	is_one_player(char **map)
{
	int	i;
	int	player_found;
	int	j;

	i = 0;
	player_found = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'O' || map[i][j] == 'E')
			{
				if (!player_found)
					player_found = 1;
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	return (player_found);
}
