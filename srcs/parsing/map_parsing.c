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

char	**read_scene(t_cub *cub, char *path)
{
	char	**scene;
	char	*line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nfailed to open file\n", 2), NULL);
	scene = malloc(sizeof(char *) * (ft_count_line(path) + 1));
	if (!scene)
		return (ft_putstr_fd("Error\nmalloc failed\n", 2), clean_exit(cub),
			close(fd), NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		scene[i] = line;
		i++;
	}
	scene[i] = NULL;
	return (close(fd), scene);
}

static int	does_map_contain_player(char **map)
{
	int	number;
	int	i;
	int	j;

	number = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				number++;
			}
			j++;
		}
		i++;
	}
	if (number != 1)
		return (0);
	return (1);
}

int	read_scene_map(t_cub *cub, char **scene, int i)
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
		return (ft_printf("Error\nMap is needed\n"), 0);
	j = 0;
	map = malloc(sizeof(char *) * (999));
	if (!map)
		return (ft_printf("Error\nMalloc failed\n"), clean_exit(cub), 0);
	while (scene[i + j])
	{
		map[j] = ft_strdup(scene[i + j]);
		if (!map[j])
			return (ft_printf("Error\nMalloc failed\n"), clean_exit(cub),
				free_arrstr(map), 0);
		j++;
	}
	map[j] = NULL;
	return (cub->map = map, 1);
}

static int	does_map_contain_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] && map[i][j] != 13
				&& map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t'
				&& map[i][j] != '0' && map[i][j] != 'N' && map[i][j] != '\n'
				&& map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != 'S')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_map_ok(t_cub *cub, char **map)
{
	if (!(map))
		return (ft_putstr_fd("Error\nMap should exist\n", 2), 0);
	if (does_map_contain_valid_chars(map))
		return (ft_putstr_fd("Error\nMap contain invalid chars\n", 2), 0);
	if (!does_map_contain_player(map))
		return (ft_putstr_fd("Error\nMap should contain 1 player\n", 2), 0);
	if (!flood_fill(cub, map))
		return (ft_putstr_fd("Error\nMap has to be closed\n", 2), 0);
	return (1);
}
