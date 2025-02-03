/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/03 21:56:15 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	interact(t_data *data)
{
	if (data->map.map[(int)data->player_y][(int)data->player_x + 1] == 'D')
		data->map.map[(int)data->player_y][(int)data->player_x + 1] = 'O';
	else if (data->map.map[(int)data->player_y][(int)data->player_x - 1] == 'D')
		data->map.map[(int)data->player_y][(int)data->player_x - 1] = 'O';
	else if (data->map.map[(int)data->player_y + 1][(int)data->player_x] == 'D')
		data->map.map[(int)data->player_y + 1][(int)data->player_x] = 'O';
	else if (data->map.map[(int)data->player_y - 1][(int)data->player_x] == 'D')
		data->map.map[(int)data->player_y - 1][(int)data->player_x] = 'O';
	else if (data->map.map[(int)data->player_y][(int)data->player_x + 1] == 'O')
		data->map.map[(int)data->player_y][(int)data->player_x + 1] = 'D';
	else if (data->map.map[(int)data->player_y][(int)data->player_x - 1] == 'O')
		data->map.map[(int)data->player_y][(int)data->player_x - 1] = 'D';
	else if (data->map.map[(int)data->player_y + 1][(int)data->player_x] == 'O')
		data->map.map[(int)data->player_y + 1][(int)data->player_x] = 'D';
	else if (data->map.map[(int)data->player_y - 1][(int)data->player_x] == 'O')
		data->map.map[(int)data->player_y - 1][(int)data->player_x] = 'D';
}

int	shot(int keycode, int x, int y, t_data *data)
{
	int	i;

	(void)x;
	(void)y;
	if (keycode == 1)
	{
		i = data->nb_entity;
		while (i--)
		{
			if (data->entity[i].targeted == 1)
			{
				data->entity[i].is_alive = 0;
				data->entity[i].targeted = 0;
				return (0);
			}
		}
	}
	return (0);
}

int	player_move(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (data->key.w)
	{
		new_x = data->player_x + data->raycast.dir_x * 0.1;
		new_y = data->player_y + data->raycast.dir_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] != '1' && data->map.map[(int)new_y][(int)new_x] != 'D')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->key.s)
	{
		new_x = data->player_x - data->raycast.dir_x * 0.1;
		new_y = data->player_y - data->raycast.dir_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] != '1' && data->map.map[(int)new_y][(int)new_x] != 'D')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->key.d)
	{
		new_x = data->player_x + data->raycast.plane_x * 0.1;
		new_y = data->player_y + data->raycast.plane_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] != '1' && data->map.map[(int)new_y][(int)new_x] != 'D')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->key.a)
	{
		new_x = data->player_x - data->raycast.plane_x * 0.1;
		new_y = data->player_y - data->raycast.plane_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] != '1' && data->map.map[(int)new_y][(int)new_x] != 'D')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	return (0);
}
