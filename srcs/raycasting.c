/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:01:46 by nferrad           #+#    #+#             */
/*   Updated: 2025/01/27 14:17:44 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// configurer la porte (is_door) dans cette fonction ?
int	check_ray_hit(t_raycast *r, t_data *data)
{
	int	side;
	int	hit;

	hit = 0;
	r->is_door = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			side = 1;
		}
		if (data->map.map[r->map_y][r->map_x] == '1')
			hit = 1;
		else if (data->map.map[r->map_y][r->map_x] == 'D')
		{
			hit = 1;
			r->is_door = 1;
		}
	}
	r->wall_dist = r->side_dist_y - r->delta_dist_y;
	if (!side)
		r->wall_dist = r->side_dist_x - r->delta_dist_x;
	return (side);
}

void	init_raycast(t_raycast *r, t_data *data, int x)
{
	r->camera_x = 2 * x / (double)WIDTH - 1;
	r->ray_dir_x = r->dir_x + r->plane_x
		*r->camera_x;
	r->ray_dir_y = r->dir_y + r->plane_y
		*r->camera_x;
	r->map_x = data->player_x;
	r->map_y = data->player_y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

void	init_ray_dir(t_data *data)
{
	t_raycast *raycast;

	raycast = &data->raycast;
	raycast->dir_x = cos(data->angle);
	raycast->dir_y = -sin(data->angle);
	raycast->plane_x = sin(data->angle) * 0.66;
	raycast->plane_y = cos(data->angle) * 0.66;
}

void	draw_limits(t_raycast *raycast, int *draw_start, int *draw_end)
{
	raycast->line_height = (int)(HEIGHT / raycast->wall_dist);
	*draw_start = -raycast->line_height / 2 + HEIGHT / 2;
	*draw_end = raycast->line_height / 2 + HEIGHT / 2;
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
