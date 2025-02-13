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

static int	generate_color(char *r, char *g, char *b)
{
	int	colors[3];

	colors[0] = ft_atoi(r);
	colors[1] = ft_atoi(g);
	colors[2] = ft_atoi(b);
	if (!colors[0] && !colors[1] && !colors[2])
		return (ft_putstr_fd("Error\nColor argument need to follow \
			this format <R>,<G>,<B>\n", 2), 0);
	if (colors[0] > 255)
		colors[0] = 255;
	if (colors[1] > 255)
		colors[1] = 255;
	if (colors[2] > 255)
		colors[2] = 255;
	return (255 << 24) + (colors[0] << 16) +
		(colors[1] << 8) + (colors[2] << 0);
}

static int	read_scene_color(t_cub *cub, char *line, int *is_parsing)
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
		split = ft_split(&(line[j + 2]), ',');
		if (!split)
			return (ft_putstr_fd("Error\nmalloc failed\n", 2),
				clean_exit(cub), 0);
		if (!split[0] || !split[1] || !split[2] || split[3])
			return (free_arrstr(split), 1);
		color = generate_color(split[0], split[1], split[2]);
		if (!color)
			return (free_arrstr(split), 1);
		if (line[j] == 'F')
			cub->f_color = color;
		else if (line[j] == 'C')
			cub->c_color = color;
		return (free_arrstr(split), *is_parsing = 1, 1);
	}
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
	path = ft_substr(line, j, k - j);
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
	if (line[j] == 'N' && line[j + 1] == 'O' && !(cub->north_path))
		return (cub->north_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(cub->south_path))
		return (cub->south_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(cub->west_path))
		return (cub->west_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(cub->east_path))
		return (cub->east_path = get_text(cub, line, j + 2), *fnd = 1, 1);
	return (1);
}

static int	read_scene_args(t_cub *cub, char **scene)
{
	int	i;
	int	is_parsing_args;

	i = 0;
	while (scene && scene[i])
	{
		is_parsing_args = 0;
		if (!read_scene_color(cub, scene[i], &is_parsing_args))
			return (free_arrstr(scene), 0);
		if (!read_scene_texture(cub, scene[i], &is_parsing_args))
			return (free_arrstr(scene), 0);
		if (!is_parsing_args && ft_strchr(scene[i], '1'))
		{
			if (read_scene_map(cub, scene, i))
				break ;
		}
		i++;
	}
	return (1);
}

static int	check_missing_args(t_cub *cub)
{
	if (!cub->north_path)
		return (ft_putstr_fd("Error\nNO ./path_to_the_north_texture\
			is needed\n", 2), 0);
	if (!cub->south_path)
		return (ft_putstr_fd("Error\nSO ./path_to_the_south_texture\
			is needed\n", 2), 0);
	if (!cub->west_path)
		return (ft_putstr_fd("Error\nWE ./path_to_the_west_texture\
			is needed\n", 2), 0);
	if (!cub->east_path)
		return (ft_putstr_fd("Error\nEA ./path_to_the_east_texture\
			is needed\n", 2), 0);
	if (!cub->f_color)
		return (ft_putstr_fd("Error\nF <R>,<G>,<B> is needed\n\"", 2), 0);
	if (!cub->c_color)
		return (ft_putstr_fd("Error\nC <R>,<G>,<B> is needed\n\"", 2), 0);
	return (1);
}

static t_texture	init_texture(char *path, void *mlx)
{
	t_texture	texture;
	texture.img =  mlx_xpm_file_to_image(mlx, path, &(texture.width),
		&(texture.height));
	texture.addr = (int *)mlx_get_data_addr(texture.img, &texture.pixel_bits,
		&texture.line_size, &texture.endian);
	if (!texture.img)
		return (ft_printf("Error\nNo image found for \"%s\"\n", path), texture);
	return (texture);
}

int	parsing(t_cub *cub, char *path)
{
	char	**scene;

	scene = read_scene(cub, path);
	if (!scene)
		return (0);
	if (!read_scene_args(cub, scene))
		return (0);
	if (!check_missing_args(cub))
		return (free_arrstr(scene), clean_exit(cub), 0);
	if (!is_map_ok(cub, cub->map))
		return (free_arrstr(scene), clean_exit(cub), 0);
	cub->north_img = init_texture(cub->north_path, cub->init);
	if (!(cub->north_img.img))
		return (free_arrstr(scene), clean_exit(cub), 0);
	cub->south_img = init_texture(cub->south_path, cub->init);
	if (!(cub->south_img.img))
		return (free_arrstr(scene), clean_exit(cub), 0);
	cub->west_img = init_texture(cub->west_path, cub->init);
	if (!(cub->west_img.img))
		return (free_arrstr(scene), clean_exit(cub), 0);
	cub->east_img = init_texture(cub->east_path, cub->init);
	if (!(cub->east_img.img))
		return (free_arrstr(scene), clean_exit(cub), 0);
	return (free_arrstr(scene), 1);
}
