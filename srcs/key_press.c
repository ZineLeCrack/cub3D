/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:07:26 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/20 13:40:39 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	can_move(int key, t_cub *cub)
{
	float	pl_coo[2];
	float	dir[2];

	pl_coo[0] = cub->player.x;
	pl_coo[1] = cub->player.y;
	dir[0] = cub->player.dir.x;
	dir[1] = cub->player.dir.y;
	if (key == 'w')
		if (cub->map[(int)floorf(pl_coo[1] + dir[1] * 0.1)]
			[(int)floorf(pl_coo[0] + dir[0] * 0.1)] != '1')
			return (1);
	if (key == 's')
		if (cub->map[(int)floorf(pl_coo[1] - dir[1] * 0.1)]
			[(int)floorf(pl_coo[0] - dir[0] * 0.1)] != '1')
			return (1);
	if (key == 'a')
		if (cub->map[(int)floorf(pl_coo[1] - dir[0] * 0.1)]
			[(int)floorf(pl_coo[0] + dir[1] * 0.1)] != '1')
			return (1);
	if (key == 'd')
		if (cub->map[(int)floorf(pl_coo[1] + dir[0] * 0.1)]
			[(int)floorf(pl_coo[0] - dir[1] * 0.1)] != '1')
			return (1);
	return (0);
}

void	moves(t_cub *cub)
{
	if (cub->keys['w'] && can_move('w', cub))
	{
		cub->player.x += cub->player.dir.x * 0.1;
		cub->player.y += cub->player.dir.y * 0.1;
	}
	if (cub->keys['s'] && can_move('s', cub))
	{
		cub->player.x -= cub->player.dir.x * 0.1;
		cub->player.y -= cub->player.dir.y * 0.1;
	}
	if (cub->keys['a'] && can_move('a', cub))
	{
		cub->player.x += cub->player.dir.y * 0.1;
		cub->player.y -= cub->player.dir.x * 0.1;
	}
	if (cub->keys['d'] && can_move('d', cub))
	{
		cub->player.x -= cub->player.dir.y * 0.1;
		cub->player.y += cub->player.dir.x * 0.1;
	}
}

void	turn_cam(t_cub *cub)
{
	float	angle;

	angle = atan2f(cub->player.dir.y, cub->player.dir.x);
	if (cub->keys[65363] == 1)
	{
		angle += M_PI / 45;
		cub->player.dir = create_vector(1, cosf(angle), sinf(angle));
	}
	if (cub->keys[65361] == 1)
	{
		angle -= M_PI / 45;
		cub->player.dir = create_vector(1, cosf(angle), sinf(angle));
	}
}

int	key_release(int key, t_cub *cub)
{
	if (key >= 0 && key <= 65536)
		cub->keys[key] = 0;
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	if (key == 65307)
		clean_exit(cub);
	if (key >= 0 && key <= 65536)
		cub->keys[key] = 1;
	return (0);
}
