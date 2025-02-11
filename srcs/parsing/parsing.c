/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:42:38 by mduvey            #+#    #+#             */
/*   Updated: 2025/02/11 19:23:02 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	**read_scene(char *path)
{
	char	**scene;
	char	*line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("error: failed to open file\n", 2), NULL);
	scene = malloc(sizeof(char *) * (ft_count_line(path) + 1));
	if (!scene)
		return (ft_putstr_fd("error: malloc failed\n", 2), NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		scene[i] = line;
		line = get_next_line(fd);
		i++;
	}
	scene[i] = NULL;
	return (scene);
}

int	read_scene_texture(t_cub *cub, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !(cub->north_path))
		cub->north_path = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(cub->south_path))
		cub->south_path = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(cub->west_path))
		cub->west_path = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(cub->east_path))
		cub->east_path = get_texture_path(line, j + 2);
	return (1);
}

int	read_scene_args(t_cub *cub, char **scene)
{
	int	i;
	int	j;

	i = 0;
	while (scene && scene[i])
	{
		j = 0;
		if (ft_isalpha(scene[i][j]) && ft_isalpha(scene[i][j + 1]))
			read_scene_texture(cub, scene[i])
		else if (scene[i][j] == 'C' || scene[i][j] == 'F')
		while (scene[i][j])
		{
		}
	}
}

int	parsing(t_cub *cub, char *path)
{
	char	**scene;

	scene = read_scene(path);
	if (!scene)
		return (0);
	if (!read_scene_args(cub, scene))
		return (free(scene), 0);
}