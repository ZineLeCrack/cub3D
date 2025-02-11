/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:53:27 by romain            #+#    #+#             */
/*   Updated: 2025/02/11 18:17:43 by mduvey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/libft/libft.h"
# include "../srcs/ft_printf/ft_printf.h"
# include "../srcs/get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define M_PI 3.14159265358979323846
# define ANGLE_STEP (M_PI / 3600)

/* STRUCTURES */

typedef struct s_vector
{
	float		x;
	float		y;
	float		n;
}	t_vector;

typedef struct s_player
{
	float		x;
	float		y;
	t_vector	dir;
	t_vector	rseg;
	t_vector	lseg;
}	t_player;

typedef struct s_cub
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			f_color;
	int			c_color;
	char		**map;
	void		*init;
	void		*win;
	int			keys[65536];
	t_player	player;
}	t_cub;

/* INIT DATA */

t_player	init_player(t_cub *cub);
int			ft_count_line(char *path);
char		**create_map(char *path);
void		init_cub(t_cub *cub, char *path);

/* KEY PRESS */

int			key_press(int key, t_cub *cub);

/* RAYCASTING FUNCTIONS */

void		draw_column(t_cub *cub, float *d, int c, int color);
int			ft_hit_wall(float x, float y, float *step, t_cub *cub);

/* UTILS */

int			clean_exit(t_cub *cub);
t_vector	create_vector(float n, float x, float y);
float		round_to_n_decimals(float number, int n);
int			is_integer(float num);

/* MAP PARSING */

int			is_map_ok(char **map);
int			is_map_closed(char **map);
int			flood_fill(char **map);
int			is_one_player(char **map);

/* FREE */

void		free_arrstr(char **array);

#endif
