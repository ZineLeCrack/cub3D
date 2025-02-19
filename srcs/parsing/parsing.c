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

int	generate_color(char *r, char *g, char *b)
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
	return ((255 << 24) + (colors[0] << 16)
		+ (colors[1] << 8) + (colors[2] << 0));
}

static int	check_missing_args(t_cub *cub)
{
	if (!cub->north_path)
		return (ft_putstr_fd("Error\nNO ./path_to_the_north_texture \
is needed\n", 2), 0);
	if (!cub->south_path)
		return (ft_putstr_fd("Error\nSO ./path_to_the_south_texture \
is needed\n", 2), 0);
	if (!cub->west_path)
		return (ft_putstr_fd("Error\nWE ./path_to_the_west_texture \
is needed\n", 2), 0);
	if (!cub->east_path)
		return (ft_putstr_fd("Error\nEA ./path_to_the_east_texture \
is needed\n", 2), 0);
	if (!cub->f_color)
		return (ft_putstr_fd("Error\nF <R>,<G>,<B> is needed\n", 2), 0);
	if (!cub->c_color)
		return (ft_putstr_fd("Error\nC <R>,<G>,<B> is needed\n", 2), 0);
	return (1);
}

static t_texture	init_texture(char *path, void *mlx)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &(texture.width),
			&(texture.height));
	if (!texture.img)
		return (ft_printf("Error\nNo image found for |--%s--|\n", path),
			texture);
	texture.addr = mlx_get_data_addr(texture.img, &texture.pixel_bits,
			&texture.line_size, &texture.endian);
	return (texture);
}

static int	init_textures(t_cub *cub, char **scene)
{
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
	return (1);
}

int	parsing(t_cub *cub, char *path)
{
	char	**scene;
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || path[len - 1] != 'b' || path[len - 2] != 'u'
		|| path[len - 3] != 'c' || path[len - 4] != '.')
		return (ft_putstr_fd("Error\nThe <map path> must be a .cub\n", 2), 0);
	scene = read_scene(cub, path);
	if (!scene || !read_scene_args(cub, scene))
		return (0);
	if (!check_missing_args(cub))
		return (free_arrstr(scene), clean_exit(cub), 0);
	if (!is_map_ok(cub, cub->map))
		return (free_arrstr(scene), clean_exit(cub), 0);
	init_textures(cub, scene);
	return (free_arrstr(scene), 1);
}
