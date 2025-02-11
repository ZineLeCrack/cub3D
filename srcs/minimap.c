/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:51:09 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/11 13:04:08 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_heigth(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
		i++;
	return (i);
}

int	get_length(t_cub *cub, float y)
{
	int	i;

	y = floorf(y);
	i = 0;
	while (cub->map[(int)y][i] && cub->map[(int)y][i] != '\n')
		i++;
	return (i);
}

static void	ft_put_decor_around_player(t_cub *cub, char *addr, int infos[3])
{
	int		mini_coo[2];
	float	tmp_coo[2];
	float	pl_coo[2];

	pl_coo[0] = cub->player.x;
	pl_coo[1] = cub->player.y;
	mini_coo[1] = 49;
	tmp_coo[1] = pl_coo[1] - 5;
	while (tmp_coo[1] < pl_coo[1] + 5)
	{
		mini_coo[0] = 1549;
		tmp_coo[0] = pl_coo[0] - 5;
		while (tmp_coo[0] < pl_coo[0] + 5)
		{
			if (tmp_coo[0] < 0 || tmp_coo[1] < 0
				|| tmp_coo[1] > get_heigth(cub)
				|| tmp_coo[0] > get_length(cub, tmp_coo[1]))
				my_mlx_pixel_put(addr, mini_coo, 0x000000, infos);
			else if (cub->map[(int)floorf(tmp_coo[1])]
				[(int)floorf(tmp_coo[0])] == '1')
				my_mlx_pixel_put(addr, mini_coo, 0xC0C0C0, infos);
			else
				my_mlx_pixel_put(addr, mini_coo, 0xFFFFFF, infos);
			tmp_coo[0] += 0.05;
			mini_coo[0]++;
		}
		mini_coo[1]++;
		tmp_coo[1] += 0.05;
	}
	return ;
}

void	draw_minimap(t_cub *cub, char *addr, int infos[3])
{
	int		px_coo[2];
	float	player_coo[2];

	player_coo[0] = cub->player.x;
	player_coo[1] = cub->player.y;
	ft_put_decor_around_player(cub, addr, infos);
	px_coo[1] = 147;
	while (++px_coo[1] < 153)
	{
		px_coo[0] = 1647;
		while (++px_coo[0] < 1653)
			my_mlx_pixel_put(addr, px_coo, 0xFF0000, infos);
	}
}
