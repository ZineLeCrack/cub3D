/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:51:45 by romain            #+#    #+#             */
/*   Updated: 2025/02/14 11:14:34 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	crosshair(char *addr, int infos[3])
{
	int	coo[2];

	coo[1] = 448;
	while (++coo[1] <= 451)
	{
		coo[0] = 889;
		while (++coo[0] <= 910)
			my_mlx_pixel_put(addr, coo, 0xFF0000, infos);
	}
	coo[0] = 898;
	while (++coo[0] <= 901)
	{
		coo[1] = 439;
		while (++coo[1] <= 460)
			my_mlx_pixel_put(addr, coo, 0xFF0000, infos);
	}
}

int	loop(t_cub *cub)
{
	void	*img;
	char	*addr;
	int		img_infos[3];
	float	angle;

	angle = atan2f(cub->player.dir.y, cub->player.dir.x) - (M_PI / 4);
	img = mlx_new_image(cub->init, 1800, 900);
	addr = mlx_get_data_addr(img, &img_infos[0], &img_infos[1], &img_infos[2]);
	turn_cam(cub);
	moves(cub);
	raytracing(cub, angle, img_infos, addr);
	crosshair(addr, img_infos);
	mlx_put_image_to_window(cub->init, cub->win, img, 0, 0);
	draw_minimap(cub, addr, img_infos);
	mlx_destroy_image(cub->init, img);
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
	mlx_hook(cub.win, 2, 1, key_press, &cub);
	mlx_hook(cub.win, 3, 2, key_release, &cub);
	mlx_hook(cub.win, 17, 0, clean_exit, &cub);
	mlx_loop_hook(cub.init, loop, &cub);
	mlx_loop(cub.init);
	return (0);
}
