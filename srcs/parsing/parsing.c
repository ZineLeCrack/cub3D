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

static int	generate_color(char *r, char *g, char *b)
{
	int	colors[3];

	colors[0] = ft_atoi(r);
	colors[1] = ft_atoi(g);
	colors[2] = ft_atoi(b);
	if (!colors[0] && !colors[1] && !colors[2])
		return (0);
	if (colors[0] > 255)
		colors[0] = 255;
	if (colors[1] > 255)
		colors[1] = 255;
	if (colors[2] > 255)
		colors[2] = 255;
	return (255 << 24) + (colors[0] << 16) + (colors[1] << 8) + (colors[2] << 0);
}

static int	read_scene_color(t_cub *cub, char *line, int *i)
{
	int		j;
	char	**split;
	int		color;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if ((line[j] == 'C' || line[j] == 'F')
		&& (line[j + 1] == ' ' || line[j + 1] == '\t'))
	{
		split = ft_split(&(line[j]), ',');
		if (!split)
			return (0);
		if (!split[0] || !split[1] || !split[3])
			return (free_arrstr(split), 0);
		color = generate_color(split[0], split[1], split[3]);
		if (!color)
			return (free_arrstr(split), 0);
		if (line[j] == 'F')
			cub->f_color = color;
		else if (line[j] == 'C')
			cub->c_color = color;
		return (free_arrstr(split), (*i)++, 1);
	}
	return (1);
}

char	*get_texture_path(char *line, int j)
{
	char	*path;
	int		k;

	k = j;
	while (line[k] && line[k] != '\n' && line[k] != ' ' && line[k] != '\t')
		k++;
	path = ft_substr(line, j, k - j);
	if (!path)
		return (NULL);
	return (path);
}

static int	read_scene_texture(t_cub *cub, char *line, int *i)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] == 'N' && line[j + 1] == 'O' && !(cub->north_path))
		return (cub->north_path = get_texture_path(line, j + 2), (*i)++, 1);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(cub->south_path))
		return (cub->south_path = get_texture_path(line, j + 2), (*i)++, 1);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(cub->west_path))
		return (cub->west_path = get_texture_path(line, j + 2), (*i)++, 1);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(cub->east_path))
		return (cub->east_path = get_texture_path(line, j + 2), (*i)++, 1);
	return (1);
}

static int	read_scene_args(t_cub *cub, char **scene)
{
	int	i;

	i = 0;
	while (scene && scene[i] && !read_scene_map(cub, scene, i))
		i++;
	{
		if (!read_scene_color(cub, scene[i], &i))
			return (free_arrstr(scene), 0);
		if (!read_scene_texture(cub, scene[i], &i))
			return (free_arrstr(scene), 0);
		i++;
	}
	return (1);
}

int	parsing(t_cub *cub, char *path)
{
	char	**scene;

	scene = read_scene(path);
	if (!scene)
		return (0);
	if (!read_scene_args(cub, scene))
		return (free(scene), 0);
	return (1);
}