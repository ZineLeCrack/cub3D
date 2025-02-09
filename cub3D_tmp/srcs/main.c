/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:51:45 by romain            #+#    #+#             */
/*   Updated: 2025/02/09 15:13:37 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	clean_exit(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
		free(cub->map[i++]);
	free(cub->map);
	mlx_destroy_window(cub->init, cub->win);
	mlx_destroy_display(cub->init);
	free(cub->init);
	exit(0);
	return (0);
}

t_vector	create_vector(float n, float x, float y)
{
	t_vector	v;

	v.n = n;
	v.x = x;
	v.y = y;
	return (v);
}

t_player	init_player(t_cub *cub)
{
	t_player	player;
	int			i;
	int			j;

	i = 0;
	player.dir = create_vector(1, cosf(0), sinf(0));
	player.rseg = create_vector(1, -1 * sinf(0), cosf(0));
	player.lseg = create_vector(1, sinf(0), -1 * cosf(0));
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'P')
			{
				player.x = j + 0.5;
				player.y = i + 0.5;
				return (player);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("error: no one \'P\' found\n", 2);
	return (player.x = -1, player.y = -1, player);
}

int	ft_count_line(char *path)
{
	int		fd;
	int		count;
	char	buf[1];
	ssize_t	size;

	fd = open(path, O_RDONLY);
	count = 1;
	while (1)
	{
		size = read(fd, buf, 1);
		if (!size)
			break ;
		if (buf[0] == '\n')
			count++;
	}
	return (count);
}

char	**create_map(char *path)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;
	
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("error: failed to open file\n", 2), NULL);
	map = malloc(sizeof(char *) * (ft_count_line(path) + 1));
	if (!map)
		return (ft_putstr_fd("error: malloc failed\n", 2), NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	init_cub(t_cub *cub, char *path)
{
	int	i;

	i = 0;
	cub->map = create_map(path);
	if (!cub->map)
		return ;
	cub->player = init_player(cub);
	if (cub->player.x == -1 && cub->player.y == -1)
	{
		while (cub->map[i])
			free(cub->map[i++]);
		free(cub->map);
		return ;
	}
	cub->init = mlx_init();
	cub->win = mlx_new_window(cub->init, 1800, 900, "cub3D");
}

int	is_integer(float num)
{
	return (floorf(num) == num);
}

float	round_to_n_decimals(float number, int n)
{
	float factor;
	
	factor = powf(10.0f, n);
	return (roundf(number * factor) / factor);
}

void	draw_column(t_cub *cub, float *d, int c, int orientation)
{
	int	h;
	int	roof_floor;
	int	y;
	
	h = (int)roundf(900 / *d);
	y = 0;
	if (h > 900)
	{
		while (y < 900)
			mlx_pixel_put(cub->init, cub->win, c, y++, orientation);
	}
	else
	{
		roof_floor = (900 - h);
		while (y < roof_floor * 0.5)
			mlx_pixel_put(cub->init, cub->win, c, y++, 0xFFFFFF);
		while (y < 900 - (roof_floor * 0.5))
			mlx_pixel_put(cub->init, cub->win, c, y++, orientation);
		while (y < 900)
			mlx_pixel_put(cub->init, cub->win, c, y++, 0xFFFFFF);
	}
}

int	loop(t_cub *cub)
{
	float	x;
	float	y;
	float	d;
	float	angle;
	float	dx, dy;
	int		column;

	column = 0;
	angle = atan2f(cub->player.dir.y, cub->player.dir.x) - (M_PI / 4);
	while (column < 1800)
	{
		x = cub->player.x;
		y = cub->player.y;
		dx = cosf(angle) * 0.01;
		dy = sinf(angle) * 0.01;
		while (1)
		{
			if (is_integer(round_to_n_decimals(x, 2)))
				if (cub->map[(int)round_to_n_decimals(x, 2)][(int)floorf(y)] == '1')
					break ;
			if (is_integer(round_to_n_decimals(y, 2)))
				if (cub->map[(int)floorf(x)][(int)round_to_n_decimals(y, 2)] == '1')
					break ;
			x += dx;
			y += dy;
		}
		d = sqrtf(((x - cub->player.x) * (x - cub->player.x))
			+ ((y - cub->player.y) * (y - cub->player.y)));
		draw_column(cub, &d, column, 0x404040);
		column++;
		angle += ANGLE_STEP;
	}
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	static float	angle = 0;

	if (key == 65362)
	{
		cub->player.x += cub->player.dir.x * 0.2;
		cub->player.y += cub->player.dir.y * 0.2;
	}
	if (key == 65364)
	{
		cub->player.x -= cub->player.dir.x * 0.2;
		cub->player.y -= cub->player.dir.y * 0.2;
	}
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
	mlx_key_hook(cub.win, key_press, &cub);
	mlx_loop_hook(cub.init,  loop, &cub);
	mlx_hook(cub.win, 17, 0, clean_exit, &cub);
	mlx_loop(cub.init);
	return (0);
}
