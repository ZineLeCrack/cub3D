/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:53:27 by romain            #+#    #+#             */
/*   Updated: 2025/02/11 10:40:33 by rlebaill         ###   ########.fr       */
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
# define ANGLE_STEP 0.000873 // (pi / 2) / 1800

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

void		moves(t_cub *cub);
void		turn_cam(t_cub *cub);
int			key_release(int key, t_cub *cub);
int			key_press(int key, t_cub *cub);

/* RAYCASTING FUNCTIONS */

void		my_mlx_pixel_put(char *addr, int coo[2], int color, int infos[3]);
void		raytracing(t_cub *cub, float angle, int infos[3], char *addr);
void		draw_column(float *d, int c[2], char *addr, int infos[3]);
int			ft_hit_wall(float x, float y, float *step, t_cub *cub);

/* MINIMAP */

void		draw_minimap(t_cub *cub, char *addr, int infos[3]);

/* UTILS */

int			clean_exit(t_cub *cub);
t_vector	create_vector(float n, float x, float y);
int			get_heigth(t_cub *cub);
int			get_length(t_cub *cub, float y);
float		round_to_n_decimals(float number, int n);
int			is_integer(float num);

#endif
