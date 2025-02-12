/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:11:59 by nferrad           #+#    #+#             */
/*   Updated: 2025/02/12 22:48:28 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->nb_entity)
		data->entity[i].distance = ((data->player_x - data->entity[i].x)
				* (data->player_x - data->entity[i].x) + (data->player_y
					- data->entity[i].y)
				* (data->player_y - data->entity[i].y));
	i = -1;
	while (++i < data->nb_entity)
	{
		j = -1;
		while (++j < data->nb_entity - 1)
		{
			if (data->entity[j].distance < data->entity[j + 1].distance)
			{
				fswap(&data->entity[j].distance, &data->entity[j + 1].distance);
				fswap(&data->entity[j].x, &data->entity[j + 1].x);
				fswap(&data->entity[j].y, &data->entity[j + 1].y);
				iswap(&data->entity[j].is_alive, &data->entity[j + 1].is_alive);
			}
		}
	}
}

void	goto_coords(t_data *data, t_entity *entity, float x, float y)
{
	float	new_x;
	float	new_y;
	float	speed;

	new_x = entity->x;
	new_y = entity->y;
	speed = 0.05;
	if (entity->x > x)
		new_x = entity->x - speed;
	if (entity->x < x)
		new_x = entity->x + speed;
	if (entity->y > y)
		new_y = entity->y - speed;
	if (entity->y < y)
		new_y = entity->y + speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1'
		&& data->map.map[(int)new_y][(int)new_x] != 'D')
	{
		entity->x = new_x;
		entity->y = new_y;
	}
}

void	get_coord(t_entity *entity, int *x, int *y)
{
	int	tmp;

	while (entity->node[*y][*x].prev_x != (int)entity->x
		|| entity->node[*y][*x].prev_y != (int)entity->y)
	{
		tmp = entity->node[*y][*x].prev_x;
		*y = entity->node[*y][*x].prev_y;
		*x = tmp;
	}
}

void	move_enemies(t_data *data, t_entity *entity)
{
	int	x;
	int	y;

	x = (int)entity->x;
	y = (int)entity->y;
	init_lists(data, entity);
	while (x != (int)data->player_x || y != (int)data->player_y)
	{
		entity->closed_list[y][x] = 1;
		entity->node[y][x].f = 99999;
		entity->nx = x;
		entity->ny = y;
		fill_node(data, entity, 1, 0);
		fill_node(data, entity, 0, 1);
		fill_node(data, entity, -1, 0);
		fill_node(data, entity, 0, -1);
		if (!check_list(data, entity))
			break ;
		find_min_node(data, entity, &x, &y);
	}
	if (!check_list(data, entity))
		return (free_lists(data, entity));
	get_coord(entity, &x, &y);
	goto_coords(data, entity, x + 0.5, y + 0.5);
	free_lists(data, entity);
}

void	enemies(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_entity)
	{
		if (data->entity[i].distance < 0.5 && data->entity[i].is_alive)
		{
			data->hp -= 1;
			if (data->hp <= 0)
			{
				ft_printf("💀 Game Over ! 💀\n");
				finish_game(data);
			}
		}
		if (data->entity[i].distance < 0.3 || data->entity[i].distance > 120
			|| !data->entity[i].is_alive)
			continue ;
		if (data->entity[i].distance > 2)
			move_enemies(data, &data->entity[i]);
		else
			goto_coords(data, &data->entity[i], data->player_x, data->player_y);
	}
}
