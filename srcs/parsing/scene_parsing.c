/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:44:30 by mduvey            #+#    #+#             */
/*   Updated: 2025/02/20 14:42:24 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*trim_n(char *str)
{
	int		start;
	int		i;
	char	*result;

	start = 0;
	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
		start++;
	i = 0;
	while (str[start + i] && str[start + i + 1] != '\n')
		i++;
	result = ft_substr(str, start, i);
	return (result);
}

int	read_scene_color(t_cub *cub, char *tmp_line, int *is_parsing)
{
	char	**split;
	int		color;
	char	*line;

	line = trim_n(&(tmp_line[2]));
	if ((tmp_line[0] == 'C' || tmp_line[0] == 'F'))
	{
		split = ft_split(line, ',');
		if (!split)
			return (ft_putstr_fd("Error\nmalloc failed\n", 2),
				free(line), clean_exit(cub), 0);
		if (!ft_strlen(split[0]) || !ft_strlen(split[1]) || !ft_strlen(split[2])
			|| split[3])
			return (ft_putstr_fd("Error\n<R>,<G>,<B>\n", 2),
				free_arrstr(split), free(line), 0);
		color = generate_color(split[0], split[1], split[2]);
		if (tmp_line[0] == 'F')
			cub->f_color = color;
		else if (tmp_line[0] == 'C')
			cub->c_color = color;
		return (free_arrstr(split), free(line), *is_parsing = 1, 1);
	}
	free(line);
	return (1);
}

static char	*get_text(t_cub *cub, char *line, int j)
{
	char	*path;
	int		k;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	k = j;
	while (line[k] && line[k] != '\n' && line[k] != ' ' && line[k] != '\t')
		k++;
	path = ft_substr(line, j, k - j - 1);
	if (!path)
		return (clean_exit(cub), NULL);
	return (path);
}

static int	read_scene_texture(t_cub *cub, char *line, int *fnd)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] == 'N' && line[j + 1] == 'O' && !(cub->north_path)
		&& line[j + 2] && (line[j + 2] == ' ' || line[j + 2] == '\t'))
		return (cub->north_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(cub->south_path)
		&& line[j + 2] && (line[j + 2] == ' ' || line[j + 2] == '\t'))
		return (cub->south_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(cub->west_path)
		&& line[j + 2] && (line[j + 2] == ' ' || line[j + 2] == '\t'))
		return (cub->west_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(cub->east_path)
		&& line[j + 2] && (line[j + 2] == ' ' || line[j + 2] == '\t'))
		return (cub->east_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	return (1);
}

int	read_scene_args(t_cub *cub, char **scene)
{
	int	i;
	int	is_parsing_args;

	i = 0;
	while (scene && scene[i])
	{
		is_parsing_args = 0;
		if (!read_scene_color(cub, scene[i], &is_parsing_args))
			return (free_arrstr(scene), clean_exit(cub), 0);
		if (!read_scene_texture(cub, scene[i], &is_parsing_args))
			return (free_arrstr(scene), clean_exit(cub), 0);
		if (!is_parsing_args && ft_strchr(scene[i], '1'))
		{
			if (read_scene_map(cub, scene, i))
				break ;
		}
		i++;
	}
	return (1);
}
