/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:50:05 by mduvey            #+#    #+#             */
/*   Updated: 2025/02/10 15:59:57 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	is_map_line_closed(char	*line)
{
	int	i;
	int	is_closed;

	i = 0;
	is_closed = 1;
	while (line[i])
	{
		if (line[i] == '0' && is_closed)
			is_closed = 0;
		else if (line[i] == '1' && !is_closed)
			is_closed = 1;
		i++;
	}
	return (is_closed);
}

static	int	is_map_collumn_closed(char **map, int j)
{
	int	i;
	int	is_closed;

	i = 0;
	is_closed = 1;
	while (map[i] && map[i][j])
	{
		if (map[i][j] == '0' && is_closed)
			is_closed = 0;
		else if (map[i][j] == '1' && !is_closed)
			is_closed = 1;
		i++;
	}
	return (is_closed);
}

int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (!is_map_line_closed(map[i]))
			return (0);
		i++;
	}
	i = 0;
	while (map[i] && map[i][j])
	{
		if (!is_map_collumn_closed(map, j))
			return (0);
		j++;
	}
	return (1);
}