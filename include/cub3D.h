/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*   By: mduvey <mduvey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:53:27 by romain            #+#    #+#             */
/*   Updated: 2025/02/12 19:53:21 by mduvey           ###   ########.fr       */
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

typedef struct s_texture
{
	int		width;
	int		height;
	void	*img;
	int		pixel_bits;
	int		line_size;
	int		endian;
	char	*addr;
}	t_texture;

typedef struct s_cub
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	t_texture	north_img;
	t_texture	south_img;
	t_texture	west_img;
	t_texture	east_img;
	int			f_color;
	int			c_color;
	char		*addr;
	int			infos[3];
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

/* RAYCASTING FUNCTIONS AND UTILS */

void		my_mlx_pixel_put(char *addr, int coo[2], int color, int infos[3]);
void		raycasting(t_cub *cub, float angle);
void		draw_column(float *d, int c[2],	float place_hit, t_cub *cub);
float		ft_hit_wall(float x, float y, float *step, t_cub *cub);
int			get_dir(float x, float y, float coo[2]);
float		ft_find_place_hit(t_cub *cub, float *x, float *y, float step[2]);
int			ft_find_color(char *img_addr, int index);
int			ft_find_index(float *line, t_texture *img, int column, float step);
int			ft_find_column(float place_hit, t_texture *img);
void		ft_draw_column_when_close(t_cub *cub, t_texture *img,
				int h, int coo[2]);

/* MINIMAP */

int			get_heigth(t_cub *cub);
int			get_length(t_cub *cub, float y);
void		draw_minimap(t_cub *cub, char *addr, int infos[3]);

/* UTILS */

int			clean_exit(t_cub *cub);
t_vector	create_vector(float n, float x, float y);
float		round_to_n_decimals(float number, int n);
int			is_integer(float num);

/* MAP PARSING */

int			parsing(t_cub *cub, char *path);
int			is_map_ok(t_cub *cub, char **map);
int			flood_fill(t_cub *cub, char **map);
int			is_one_player(char **map);
int			read_scene_color(t_cub *cub, char *line, int *is_parsing);
int			read_scene_args(t_cub *cub, char **scene);
char		**read_scene(t_cub *cub, char *path);
int			generate_color(char *r, char *g, char *b);
int			read_scene_map(t_cub *cub, char **scene, int i);

/* FREE */

void		free_arrstr(char **array);

#endif
