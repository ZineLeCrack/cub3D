/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:07:26 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/10 13:13:58 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	moves(int key, t_cub *cub)
{
	if (key == 'w')
	{
		cub->player.x += cub->player.dir.x * 0.2;
		cub->player.y += cub->player.dir.y * 0.2;
	}
	if (key == 's')
	{
		cub->player.x -= cub->player.dir.x * 0.2;
		cub->player.y -= cub->player.dir.y * 0.2;
	}
	if (key == 'a')
	{
		cub->player.x += cub->player.dir.y * 0.2;
		cub->player.y -= cub->player.dir.x * 0.2;
	}
	if (key == 'd')
	{
		cub->player.x -= cub->player.dir.y * 0.2;
		cub->player.y += cub->player.dir.x * 0.2;
	}
}

static void	turn_cam(int key, t_cub *cub)
{
	static float	angle = 0;

	if (key == 65363)
	{
		angle += M_PI / 45;
		cub->player.dir = create_vector(1, cosf(angle), sinf(angle));
	}
	if (key == 65361)
	{
		angle -= M_PI / 45;
		cub->player.dir = create_vector(1, cosf(angle), sinf(angle));
	}
}

int	key_press(int key, t_cub *cub)
{
	if (key == 65307)
		clean_exit(cub);
	moves(key, cub);
	turn_cam(key, cub);
	return (0);
}
