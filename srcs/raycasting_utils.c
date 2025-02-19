/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:37 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/19 18:24:32 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	ft_find_place_hit(t_cub *cub, float *x, float *y, float step[2])
{
	float	place_hit;

	while (1)
	{
		place_hit = ft_hit_wall(*x, *y, step, cub);
		if (place_hit != -1)
			break ;
		*x += step[0];
		*y += step[1];
	}
	return (place_hit);
}

int	ft_find_color(char *img_addr, int index)
{
	return ((img_addr[index] & 0xFF)
		| ((img_addr[index + 1] & 0xFF) << 8)
		| ((img_addr[index + 2] & 0xFF) << 16));
}

int	ft_find_index(float *line, int img_size[2], int column, float step)
{
	int	texy;

	texy = (int)(*line);
	if (texy < 0)
		texy = 0;
	if (texy >= img_size[1])
		texy = img_size[1] - 1;
	*line += step;
	return ((texy * img_size[0] * 4) + column * 4);
}

int	ft_find_column(float place_hit, int img_size[2])
{
	int	column;

	column = (int)(place_hit * img_size[0]);
	if (column < 0)
		column = 0;
	if (column >= img_size[0])
		column = img_size[0] - 1;
	return (column);
}

void	ft_draw_column_when_close(t_cub *cub, char *img_addr,
			int img_size[2], int h, int coo[2])
{
	(void)img_addr;
	(void)img_size;
	(void)h;
	while (++coo[1] < 900)
		my_mlx_pixel_put(cub->addr, coo, 0xFF0000, cub->infos);
	return ;
}
