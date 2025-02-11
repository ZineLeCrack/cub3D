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

char		**read_scene_map(char **scene, int i)
{
	char	**map;
	int		j;

	while (scene[i])
	{
		if (ft_strlen(scene[i]) != 0)
			break ;
		i++;
	}
	if (!scene[i])
		return (ft_printf("parsing error: map is needed\n"), NULL);
	j = 0;
	map = malloc(sizeof(char *) * (999));
	if (!map)
		return (ft_printf("malloc error\n"), NULL);
	while (scene[i + j])
	{
		map[j] = ft_strdup(scene[i + j]);
		if (!map[j])
			return (ft_printf("malloc error\n"), free_arrstr(map), NULL);
		j++;
	}
	map[j] = NULL;
	return (map);
}

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
