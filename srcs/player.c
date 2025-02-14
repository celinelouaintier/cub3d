/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/14 01:01:14 by clouaint         ###   ########.fr       */
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
		data->shot = 1;
		while (i--)
		{
			if (data->entity[i].targeted == 1)
			{
				data->entity[i].is_alive = 0;
				data->entity[i].targeted = 0;
				data->killed++;
				if (data->killed == data->nb_entity)
				{
					ft_printf("👑 You won ! 👑\n");
					finish_game(data);
				}
				return (0);
			}
		}
	}
	return (0);
}

int	is_wall_or_door(t_data *data, float x, float y)
{
	char	cell;

	cell = data->map.map[(int)y][(int)x];
	if (cell == '1' || cell == 'D')
		return (1);
	return (0);
}

void	move_player(t_data *data, float dir_x, float dir_y)
{
	float	new_x;
	float	new_y;
	float	hitbox;
	int		blocked_x;
	int		blocked_y;

	hitbox = 0.1;
	new_x = data->player_x + dir_x * data->speed;
	new_y = data->player_y + dir_y * data->speed;
	blocked_x = is_wall_or_door(data, new_x + hitbox, data->player_y + hitbox)
		|| is_wall_or_door(data, new_x - hitbox, data->player_y + hitbox)
		|| is_wall_or_door(data, new_x + hitbox, data->player_y - hitbox)
		|| is_wall_or_door(data, new_x - hitbox, data->player_y - hitbox);
	blocked_y = is_wall_or_door(data, data->player_x + hitbox, new_y + hitbox)
		|| is_wall_or_door(data, data->player_x - hitbox, new_y + hitbox)
		|| is_wall_or_door(data, data->player_x + hitbox, new_y - hitbox)
		|| is_wall_or_door(data, data->player_x - hitbox, new_y - hitbox);
	if (!blocked_x)
		data->player_x = new_x;
	if (!blocked_y)
		data->player_y = new_y;
}

int	player_move(t_data *data)
{
	if (data->key.w)
		move_player(data, data->raycast.dir_x, data->raycast.dir_y);
	if (data->key.s)
		move_player(data, -data->raycast.dir_x, -data->raycast.dir_y);
	if (data->key.d)
		move_player(data, data->raycast.plane_x, data->raycast.plane_y);
	if (data->key.a)
		move_player(data, -data->raycast.plane_x, -data->raycast.plane_y);
	return (0);
}
