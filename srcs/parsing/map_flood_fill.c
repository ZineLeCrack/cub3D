/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:15:15 by mduvey            #+#    #+#             */
/*   Updated: 2025/02/10 17:11:16 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	arrstrlen(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

static char	**dup_map(char **map)
{
	int		i;
	char	**dup;

	i = 0;
	dup = malloc(sizeof(char *) * (arrstrlen(map) + 1));
	if (!dup)
		return (NULL);
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
			free_arrstr(map);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

static int	dfs(char **map, int x, int y)
{
	if (x >= 0 && y >= 0)
	{
		if (!map[x] || !map[x][y] || (map[x][y] != '0' && map[x][y] != '1'
			&& map[x][y] != 'N' && map[x][y] != 'S' && map[x][y] != 'W'
			&& map[x][y] != 'E' && map[x][y] != 'V'))
			return (0);
		if (map && map[x] && map[x][y]
			&& (map[x][y] == '0' || map[x][y] == 'S' || map[x][y] == 'N'
				|| map[x][y] == 'W' || map[x][y] == 'E'))
		{
			map[x][y] = 'V';
			if (x == 0 || y == 0)
				return (0);
			if (x - 1 >= 0 && y - 1 >= 0)
				if (!dfs(map, x - 1, y - 1))
					return (0);
			if (x - 1 >= 0)
			{
				if (!dfs(map, x - 1, y))
					return (0);
				if (!dfs(map, x - 1, y + 1))
					return (0);
			}
			if (y - 1 >= 0)
			{
				if (!dfs(map, x, y - 1))
					return (0);
				if (!dfs(map, x + 1, y - 1))
					return (0);
			}
			if (!dfs(map, x + 1, y + 1))
				return (0);
			if (!dfs(map, x + 1, y))
				return (0);
			if (!dfs(map, x, y + 1))
				return (0);
		}
	}
	return (1);
}

int	flood_fill(t_cub *cub, char **map)
{
	char	**dup;
	int		i;
	int		j;

	dup = dup_map(map);
	if (!dup)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), clean_exit(cub), 0);
	i = 0;
	while (dup[i])
	{
		j = 0;
		while (dup[i][j])
		{
			if (dup[i][j] == 'N' || dup[i][j] == 'W'
				|| dup[i][j] == 'E' || dup[i][j] == 'S')
				if (!dfs(dup, i, j))
					return (free_arrstr(dup), 0);
			j++;
		}
		i++;
	}
	free_arrstr(dup);
	return (1);
}
