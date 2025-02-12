/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:36:32 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/10 13:09:36 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
	if (cub->init)
	{
		mlx_destroy_window(cub->init, cub->win);
		mlx_destroy_display(cub->init);
		free(cub->init);
	}
	exit(0);
	return (0);
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

int	is_integer(float num)
{
	return (floorf(num) == num);
}
