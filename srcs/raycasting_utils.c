/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:37 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/19 16:57:08 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	ft_find_place_hit(t_cub *cub, float *x, float *y, float step[2])
{
	float	place_hit;

	while (1)
	{
		place_hit = ft_hit_wall(*x, *y, step, cub);
		if (place_hit != -1)
			break ;
		*x += step[0];
		*y += step[1];
	}
	return (place_hit);
}
