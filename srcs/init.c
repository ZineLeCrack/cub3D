/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:38:41 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/10 15:56:29 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
	if (!is_map_ok(map))
		return (NULL);
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
