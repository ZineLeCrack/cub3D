/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:51:45 by romain            #+#    #+#             */
/*   Updated: 2025/02/10 15:12:06 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	loop(t_cub *cub)
{
	float	coo[2];
	float	d;
	float	angle;
	float	step[2];
	int		column;

	column = 0;
	angle = atan2f(cub->player.dir.y, cub->player.dir.x) - (M_PI / 4);
	while (column < 1800)
	{
		coo[0] = cub->player.x;
		coo[1] = cub->player.y;
		step[0] = cosf(angle) * 0.005;
		step[1] = sinf(angle) * 0.005;
		while (!ft_hit_wall(coo[0], coo[1], step, cub))
		{
			coo[0] += step[0];
			coo[1] += step[1];
		}
		d = sqrtf(((coo[0] - cub->player.x) * (coo[0] - cub->player.x))
				+ ((coo[1] - cub->player.y) * (coo[1] - cub->player.y)));
		draw_column(cub, &d, column++, 0x404040);
		angle += ANGLE_STEP;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	(void)ac;
	if (ac != 2)
		return (ft_putstr_fd("usage: ./cub3D <map path>\n", 2), 1);
	init_cub(&cub, av[1]);
	if (!cub.map || cub.player.x == -1 || cub.player.y == -1)
		return (1);
	mlx_loop_hook(cub.init, loop, &cub);
	mlx_hook(cub.win, 2, 1, key_press, &cub);
	mlx_hook(cub.win, 17, 0, clean_exit, &cub);
	mlx_loop(cub.init);
	return (0);
}
