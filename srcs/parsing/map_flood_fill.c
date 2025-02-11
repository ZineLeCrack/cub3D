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

static void	dfs(char **map, int x, int y)
{
	if (x >= 0 && y >= 0)
	{
		if (map && map[x] && map[x][y] && (map[x][y] == '0' || map[x][y] == 'P'))
		{
			map[x][y] = 'V';
			if (x - 1 >= 0)
				dfs(map, x - 1, y);
			if (y - 1 >= 0)
				dfs(map, x, y - 1);
			dfs(map, x + 1, y);
			dfs(map, x, y + 1);
		}
	}
}

static int	dfs_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				return (printf("map[%i, %i] = %c", i, j, map[i][j]), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	flood_fill(char **map)
{
	char	**dup;
	int		result;
	int		i;
	int		j;

	dup = dup_map(map);
	if (!dup)
		return (ft_putstr_fd("error: malloc failed\n", 2),
			free_arrstr(map), 0);
	i = 0;
	while (dup[i])
	{
		j = 0;
		while (dup[i][j])
		{
			if (dup[i][j] == 'P')
				dfs(dup, i, j);
			j++;
		}
		i++;
	}
	result = dfs_check(dup);
	free(dup);
	return (result);
}
