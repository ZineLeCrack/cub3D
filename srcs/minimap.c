/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:51:09 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/10 18:45:34 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_minimap(t_cub *cub, char *addr, int infos[3])
{
	int		px_coo[2];
	float	player_coo[2];

	player_coo[0] = cub->player.x;
	player_coo[1] = cub->player.y;
	px_coo[1] = 49;
	while (++px_coo[1] < 250)
	{
		px_coo[0] = 1549;
		while (++px_coo[0] < 1750)
			my_mlx_pixel_put(addr, px_coo, 0x000000, infos);
	}
}
