/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:01:46 by nferrad           #+#    #+#             */
/*   Updated: 2025/01/04 19:26:41 by nferrad          ###   ########.fr       */
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
		if (data->raycast.side_dist_x < data->raycast.side_dist_y)
		{
			data->raycast.side_dist_x += data->raycast.delta_dist_x;
			data->raycast.map_x += data->raycast.step_x;
			side = 0;
		}
		else
		{
			data->raycast.side_dist_y += data->raycast.delta_dist_y;
			data->raycast.map_y += data->raycast.step_y;
			side = 1;
		}
		if (data->map.map[data->raycast.map_y][data->raycast.map_x] == '1')
			hit = 1;
	}
	return (side);
}

void	init_raycast(t_data *data, double dirX, double dirY, int x)
{
	data->raycast.camera_x = 2 * x / (double)WIDTH - 1;
	data->raycast.ray_dir_x = dirX + data->raycast.plane_x
		* data->raycast.camera_x;
	data->raycast.ray_dir_y = dirY + data->raycast.plane_y
		* data->raycast.camera_x;
	data->raycast.map_x = data->player_x;
	data->raycast.map_y = data->player_y;
	data->raycast.delta_dist_x = fabs(1 / data->raycast.ray_dir_x);
	data->raycast.delta_dist_y = fabs(1 / data->raycast.ray_dir_y);
}

void	set_step(t_data *data)
{
	if (data->raycast.ray_dir_x < 0)
	{
		data->raycast.step_x = -1;
		data->raycast.side_dist_x = (data->player_x - data->raycast.map_x)
			* data->raycast.delta_dist_x;
	}
	else
	{
		data->raycast.step_x = 1;
		data->raycast.side_dist_x = (data->raycast.map_x + 1.0 - data->player_x)
			* data->raycast.delta_dist_x;
	}
	if (data->raycast.ray_dir_y < 0)
	{
		data->raycast.step_y = -1;
		data->raycast.side_dist_y = (data->player_y - data->raycast.map_y)
			* data->raycast.delta_dist_y;
	}
	else
	{
		data->raycast.step_y = 1;
		data->raycast.side_dist_y = (data->raycast.map_y + 1.0 - data->player_y)
			* data->raycast.delta_dist_y;
	}
}
