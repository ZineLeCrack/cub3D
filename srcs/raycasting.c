/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:37:46 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/18 17:56:25 by rlebaill         ###   ########.fr       */
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

void	draw_column(float *d, int c[4], char *addr, int infos[3],
	float place_hit, t_cub *cub)
{
	int	h;
	int	roof_floor;
	int	color;
	int	coo[2];

	h = (int)roundf(900 / *d);
	coo[0] = c[0];
	coo[1] = -1;

	if (h < 0 || h >= 900)
		while (++coo[1] < 900)
			my_mlx_pixel_put(addr, coo, 0xFF0000, infos);
	roof_floor = (900 - h);
	while (++coo[1] < roof_floor * 0.5)
		my_mlx_pixel_put(addr, coo, c[3], infos);

	int	width = cub->north_img.width;
	int	height = cub->north_img.height;

	int collumn = (int)(place_hit * width);
	if (collumn < 0) collumn = 0;
	if (collumn >= width) collumn = width - 1;

	float line = 0.0;
	float step = (float)height / (float)h;

	while (++coo[1] < 900 - (roof_floor * 0.5))
	{
		int texY = (int)line;
		if (texY < 0) texY = 0;
		if (texY >= height) texY = height - 1;
		int index = (texY * width * 4) + collumn * 4;
		// if (index < 0 || index >= width * height) continue;
		color = (cub->north_img.addr[index] & 0xFF)
				| ((cub->north_img.addr[index + 1] & 0xFF) << 8)
				| ((cub->north_img.addr[index + 2] & 0xFF) << 16);
		my_mlx_pixel_put(addr, coo, color, infos);
		line += step;
	}

	while (++coo[1] < 900)
		my_mlx_pixel_put(addr, coo, c[2], infos);
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
	int		c[4];
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
		while (1)
		{
			place_hit = ft_hit_wall(coo[0], coo[1], step, cub);
			if (place_hit != -1)
				break ;
			coo[0] += step[0];
			coo[1] += step[1];
		}
		d = sqrtf(((coo[0] - cub->player.x) * (coo[0] - cub->player.x))
				+ ((coo[1] - cub->player.y) * (coo[1] - cub->player.y)))
				* cosf(angle - atan2f(cub->player.dir.y, cub->player.dir.x));
		c[1] = get_dir(step[0], step[1], coo);
		c[2] = cub->c_color;
		c[3] = cub->f_color;
		draw_column(&d, c, addr, infos, place_hit, cub);
		c[0]++;
		angle += ANGLE_STEP;
	}
}
