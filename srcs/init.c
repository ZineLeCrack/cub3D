/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:38:41 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/11 18:57:31 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_player_dir(t_player *player, char **map, int i, int j)
{
	player->x = j + 0.5;
	player->y = i + 0.5;
	if (map[i][j] == 'N')
		player->dir = create_vector(1, cosf(0), sinf(0));
	if (map[i][j] == 'E')
		player->dir = create_vector(1, cosf(0), sinf(0));
	if (map[i][j] == 'S')
		player->dir = create_vector(1, cosf(0), sinf(0));
	if (map[i][j] == 'O')
		player->dir = create_vector(1, cosf(0), sinf(0));
	return (0);
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
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'O' || cub->map[i][j] == 'E')
			{
				init_player_dir(&player, cub->map, i, j);
				return (player);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error: Map should contain one player\n", 2);
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

void	init_cub(t_cub *cub, char *path)
{
	int	i;

	i = 0;
	cub->init = NULL;
	cub->win = NULL;
	cub->north_path = NULL;
	cub->south_path = NULL;
	cub->west_path = NULL;
	cub->east_path = NULL;
	cub->c_color = 0;
	cub->f_color = 0;
	cub->map = NULL;
	if (!parsing(cub, path))
		return ;
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
