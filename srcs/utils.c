/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:36:32 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/11 16:18:24 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_dir(float x, float y, float a)
{
	if (x > 0 && y > 0)
	{
		if (is_integer(round_to_n_decimals(a, 2)))
			return (2);
		return (1);
	}
	else if (x > 0 && y < 0)
	{
		if (is_integer(round_to_n_decimals(a, 2)))
			return (2);
		return (0);
	}
	else if (x < 0 && y > 0)
	{
		if (is_integer(round_to_n_decimals(a, 2)))
			return (3);
		return (1);
	}
	else
	{
		if (is_integer(round_to_n_decimals(a, 2)))
			return (3);
		return (0);
	}
}

int	clean_exit(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
		free(cub->map[i++]);
	free(cub->map);
	mlx_destroy_window(cub->init, cub->win);
	mlx_destroy_display(cub->init);
	free(cub->init);
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
