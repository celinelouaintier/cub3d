/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:01:46 by nferrad           #+#    #+#             */
/*   Updated: 2025/01/04 00:12:04 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ray_hit(t_data *data)
{
	int	side;
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->raycast.sideDistX < data->raycast.sideDistY)
		{
			data->raycast.sideDistX += data->raycast.deltaDistX;
			data->raycast.mapX += data->raycast.stepX;
			side = 0;
		}
		else
		{
			data->raycast.sideDistY += data->raycast.deltaDistY;
			data->raycast.mapY += data->raycast.stepY;
			side = 1;
		}
		if (data->map.map[data->raycast.mapY][data->raycast.mapX] == '1')
			hit = 1;
	}
	return (side);
}

void	init_raycast(t_data *data, double dirX, double dirY, int x)
{
	data->raycast.cameraX = 2 * x / (double)WIDTH - 1;
	data->raycast.rayDirX = dirX + data->raycast.planeX * data->raycast.cameraX;
	data->raycast.rayDirY = dirY + data->raycast.planeY * data->raycast.cameraX;
	data->raycast.mapX = data->player_x;
	data->raycast.mapY = data->player_y;
	data->raycast.deltaDistX = fabs(1 / data->raycast.rayDirX);
	data->raycast.deltaDistY = fabs(1 / data->raycast.rayDirY);
}

void	set_step(t_data *data)
{
	if (data->raycast.rayDirX < 0)
	{
		data->raycast.stepX = -1;
		data->raycast.sideDistX = (data->player_x - data->raycast.mapX)
			* data->raycast.deltaDistX;
	}
	else
	{
		data->raycast.stepX = 1;
		data->raycast.sideDistX = (data->raycast.mapX + 1.0 - data->player_x)
			* data->raycast.deltaDistX;
	}
	if (data->raycast.rayDirY < 0)
	{
		data->raycast.stepY = -1;
		data->raycast.sideDistY = (data->player_y - data->raycast.mapY)
			* data->raycast.deltaDistY;
	}
	else
	{
		data->raycast.stepY = 1;
		data->raycast.sideDistY = (data->raycast.mapY + 1.0 - data->player_y)
			* data->raycast.deltaDistY;
	}
}
