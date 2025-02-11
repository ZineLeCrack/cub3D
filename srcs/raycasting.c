/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:37:46 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/10 15:12:10 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_column(t_cub *cub, float *d, int c, int color)
{
	int	h;
	int	roof_floor;
	int	y;

	h = (int)roundf(900 / *d);
	y = 0;
	if (h > 900)
	{
		while (y < 900)
			mlx_pixel_put(cub->init, cub->win, c, y++, color);
	}
	else
	{
		roof_floor = (900 - h);
		while (y < roof_floor * 0.5)
			mlx_pixel_put(cub->init, cub->win, c, y++, 0xC0C0C0);
		while (y < 900 - (roof_floor * 0.5))
			mlx_pixel_put(cub->init, cub->win, c, y++, color);
		while (y < 900)
			mlx_pixel_put(cub->init, cub->win, c, y++, 0xFFFFFF);
	}
}

int	ft_hit_wall(float x, float y, float *step, t_cub *cub)
{
	if (is_integer(round_to_n_decimals(y, 2)))
	{
		if (step[1] > 0)
		{
			if (cub->map[(int)round_to_n_decimals(y, 2)][(int)floorf(x)] == '1')
				return (1);
		}
		else if (step[1] < 0)
			if (cub->map[(int)round_to_n_decimals(y, 2) - 1][(int)floorf(x)]
				== '1')
				return (1);
	}
	else if (is_integer(round_to_n_decimals(x, 2)))
	{
		if (step[0] > 0)
		{
			if (cub->map[(int)floorf(y)][(int)round_to_n_decimals(x, 2)] == '1')
				return (1);
		}
		else if (step[0] < 0)
			if (cub->map[(int)floorf(y)][(int)round_to_n_decimals(x, 2) - 1]
				== '1')
				return (1);
	}
	return (0);
}
