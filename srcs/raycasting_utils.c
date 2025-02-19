/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:37 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/19 18:44:32 by rlebaill         ###   ########.fr       */
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

int	ft_find_index(float *line, t_texture *img, int column, float step)
{
	int	texy;

	texy = (int)(*line);
	if (texy < 0)
		texy = 0;
	if (texy >= img->height)
		texy = img->height - 1;
	*line += step;
	return ((texy * img->width * 4) + column * 4);
}

int	ft_find_column(float place_hit, t_texture *img)
{
	int	column;

	column = (int)(place_hit * img->width);
	if (column < 0)
		column = 0;
	if (column >= img->width)
		column = img->width - 1;
	return (column);
}

void	ft_draw_column_when_close(t_cub *cub, t_texture *img,
			int h, int coo[2])
{
	(void)img;
	(void)h;
	while (++coo[1] < 900)
		my_mlx_pixel_put(cub->addr, coo, 0xFF0000, cub->infos);
	return ;
}
