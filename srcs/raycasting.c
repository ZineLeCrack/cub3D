/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:37:46 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/20 14:08:16 by mduvey           ###   ########.fr       */
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

t_texture	*put_img_infos(int dir, t_cub *cub)
{
	if (dir == 0)
	{
		return (&cub->north_img);
	}
	if (dir == 1)
	{
		return (&cub->south_img);
	}
	if (dir == 2)
	{
		return (&cub->east_img);
	}
	else
	{
		return (&cub->west_img);
	}
}

void	draw_column(float *d, int c[2],	float place_hit, t_cub *cub)
{
	int			height;
	int			coo[2];
	t_texture	*img;
	float		step;
	float		line;

	img = put_img_infos(c[1], cub);
	cub->h = (int)roundf(900 / *d);
	if (cub->h < 0)
		cub->h = 0;
	coo[0] = c[0];
	coo[1] = -1;
	if (cub->h >= 900)
		return (ft_draw_column_when_close(cub, img, coo, place_hit));
	height = (900 - cub->h) * 0.5;
	while (++coo[1] < height)
		my_mlx_pixel_put(cub->addr, coo, cub->c_color, cub->infos);
	line = 0.0;
	step = (float)img->width / (float)cub->h;
	while (++coo[1] < 900 - height)
		my_mlx_pixel_put(cub->addr, coo, ft_find_color(img->addr,
				ft_find_index(&line, img,
					ft_find_column(place_hit, img), step)), cub->infos);
	while (++coo[1] < 900)
		my_mlx_pixel_put(cub->addr, coo, cub->f_color, cub->infos);
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

void	raycasting(t_cub *cub, float angle)
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
		draw_column(&d, c, place_hit, cub);
		c[0]++;
		angle += ANGLE_STEP;
	}
}
