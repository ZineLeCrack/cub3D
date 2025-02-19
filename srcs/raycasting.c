/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:37:46 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/19 16:56:40 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(char *addr, int coo[2], int color, int infos[3])
{
	char	*dst;

	if (coo[0] < 0 || coo[0] >= 1800 || coo[1] < 0 || coo[1] >= 900)
		return ;
	dst = addr + (coo[1] * infos[1] + coo[0] * (infos[0] / 8));
	*(unsigned int *)dst = color;
}

char	*put_img_infos(int dir, int *w, int *h, t_cub *cub)
{
	if (dir == 0)
	{
		*w = cub->north_img.width;
		*h = cub->north_img.height;
		return (cub->north_img.addr);
	}
	if (dir == 1)
	{
		*w = cub->south_img.width;
		*h = cub->south_img.height;
		return (cub->south_img.addr);
	}
	if (dir == 2)
	{
		*w = cub->east_img.width;
		*h = cub->east_img.height;
		return (cub->east_img.addr);
	}
	else
	{
		*w = cub->west_img.width;
		*h = cub->west_img.height;
		return (cub->west_img.addr);
	}
}

void	draw_column(float *d, int c[2], char *addr, int infos[3],
	float place_hit, t_cub *cub)
{
	int		h;
	int		index;
	int		roof_floor;
	int		color;
	int		coo[2];
	int		column;
	int		img_size[2];
	int		texy;
	char	*img_addr;
	float	step;
	float	line;

	img_addr = put_img_infos(c[1], &img_size[0], &img_size[1], cub);
	h = (int)roundf(900 / *d);
	coo[0] = c[0];
	coo[1] = -1;
	if (h < 0 || h >= 900)
	{
		while (++coo[1] < 900)
			my_mlx_pixel_put(addr, coo, 0xFF0000, infos);
		return ;
	}
	roof_floor = (900 - h);
	while (++coo[1] < roof_floor * 0.5)
		my_mlx_pixel_put(addr, coo, cub->f_color, infos);
	column = (int)(place_hit * img_size[0]);
	if (column < 0)
		column = 0;
	if (column >= img_size[0])
		column = img_size[0] - 1;
	line = 0.0;
	step = (float)img_size[1] / (float)h;
	while (++coo[1] < 900 - (roof_floor * 0.5))
	{
		texy = (int)line;
		if (texy < 0)
			texy = 0;
		if (texy >= img_size[1])
			texy = img_size[1] - 1;
		index = (texy * img_size[0] * 4) + column * 4;
		color = (img_addr[index] & 0xFF)
			| ((img_addr[index + 1] & 0xFF) << 8)
			| ((img_addr[index + 2] & 0xFF) << 16);
		my_mlx_pixel_put(addr, coo, color, infos);
		line += step;
	}
	while (++coo[1] < 900)
		my_mlx_pixel_put(addr, coo, cub->c_color, infos);
}

float	ft_hit_wall(float x, float y, float *step, t_cub *cub)
{
	if (is_integer(round_to_n_decimals(y, 2)))
	{
		if (step[1] > 0)
		{
			if (cub->map[(int)round_to_n_decimals(y, 2)][(int)floorf(x)] == '1')
				return (fmod(x, 1.0));
		}
		else if (step[1] < 0)
			if (cub->map[(int)round_to_n_decimals(y, 2) - 1][(int)floorf(x)]
				== '1')
				return (fmod(x, 1.0));
	}
	if (is_integer(round_to_n_decimals(x, 2)))
	{
		if (step[0] > 0)
		{
			if (cub->map[(int)floorf(y)][(int)round_to_n_decimals(x, 2)] == '1')
				return (fmod(y, 1.0));
		}
		else if (step[0] < 0)
			if (cub->map[(int)floorf(y)][(int)round_to_n_decimals(x, 2) - 1]
				== '1')
				return (fmod(y, 1.0));
	}
	return (-1);
}

void	raycasting(t_cub *cub, float angle, int infos[3], char *addr)
{
	int		c[2];
	float	d;
	float	step[2];
	float	coo[2];
	float	place_hit;

	c[0] = 0;
	while (c[0] < 1800)
	{
		coo[0] = cub->player.x;
		coo[1] = cub->player.y;
		step[0] = cosf(angle) * 0.01;
		step[1] = sinf(angle) * 0.01;
		place_hit = ft_find_place_hit(cub, &coo[0], &coo[1], step);
		d = sqrtf(((coo[0] - cub->player.x) * (coo[0] - cub->player.x))
				+ ((coo[1] - cub->player.y) * (coo[1] - cub->player.y)))
			* cosf(angle - atan2f(cub->player.dir.y, cub->player.dir.x));
		c[1] = get_dir(step[0], step[1], coo);
		draw_column(&d, c, addr, infos, place_hit, cub);
		c[0]++;
		angle += ANGLE_STEP;
	}
}
