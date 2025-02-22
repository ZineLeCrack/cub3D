/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:36:32 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:20 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_dir(float x, float y, float coo[2])
{
	static int	tmp = 0;

	if (is_integer(round_to_n_decimals(coo[0], 2))
		&& is_integer(round_to_n_decimals(coo[1], 2)))
		return (tmp);
	if (x > 0)
	{
		if (is_integer(round_to_n_decimals(coo[0], 2)))
		{
			if (is_integer(round_to_n_decimals(coo[1], 2)))
				return (tmp = (y > 0));
			return (tmp = 2);
		}
		return (tmp = (y > 0));
	}
	if (is_integer(round_to_n_decimals(coo[0], 2)))
	{
		if (is_integer(round_to_n_decimals(coo[1], 2)))
			return (tmp = (y > 0));
		return (tmp = 3);
	}
	return (tmp = (y > 0));
}

static void	clean_exit_data(t_cub *cub)
{
	if (cub->north_path)
		free(cub->north_path);
	if (cub->south_path)
		free(cub->south_path);
	if (cub->west_path)
		free(cub->west_path);
	if (cub->east_path)
		free(cub->east_path);
}

int	clean_exit(t_cub *cub)
{
	int	i;

	i = 0;
	clean_exit_data(cub);
	if (cub->map)
	{
		while (cub->map[i])
			free(cub->map[i++]);
		free(cub->map);
	}
	if (cub->north_img.img)
		mlx_destroy_image(cub->init, cub->north_img.img);
	if (cub->south_img.img)
		mlx_destroy_image(cub->init, cub->south_img.img);
	if (cub->east_img.img)
		mlx_destroy_image(cub->init, cub->east_img.img);
	if (cub->west_img.img)
		mlx_destroy_image(cub->init, cub->west_img.img);
	if (cub->init)
	{
		mlx_destroy_window(cub->init, cub->win);
		mlx_destroy_display(cub->init);
		free(cub->init);
	}
	return (exit(0), 0);
}

t_vector	create_vector(float n, float x, float y)
{
	t_vector	v;

	v.n = n;
	v.x = x;
	v.y = y;
	return (v);
}

float	round_to_n_decimals(float number, int n)
{
	float	factor;

	factor = powf(10, n);
	return (roundf(number * factor) / factor);
}
