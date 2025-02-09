/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:53:27 by romain            #+#    #+#             */
/*   Updated: 2025/02/09 12:43:20 by romain           ###   ########.fr       */
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

#endif
