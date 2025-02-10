/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:07:26 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/10 17:48:49 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	moves(t_cub *cub)
{
	if (cub->keys['w'])
	{
		cub->player.x += cub->player.dir.x * 0.2;
		cub->player.y += cub->player.dir.y * 0.2;
	}
	if (cub->keys['s'])
	{
		cub->player.x -= cub->player.dir.x * 0.2;
		cub->player.y -= cub->player.dir.y * 0.2;
	}
	if (cub->keys['a'])
	{
		cub->player.x += cub->player.dir.y * 0.2;
		cub->player.y -= cub->player.dir.x * 0.2;
	}
	if (cub->keys['d'])
	{
		cub->player.x -= cub->player.dir.y * 0.2;
		cub->player.y += cub->player.dir.x * 0.2;
	}
}

void	turn_cam(t_cub *cub)
{
	static float	angle = 0;

	if (cub->keys[65363])
	{
		angle += M_PI / 45;
		cub->player.dir = create_vector(1, cosf(angle), sinf(angle));
	}
	if (cub->keys[65361])
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
