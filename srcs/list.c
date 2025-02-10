/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:09:41 by nferrad           #+#    #+#             */
/*   Updated: 2025/02/10 17:41:16 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_list(t_data *data, t_entity *entity)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (data->map.map[i][++j])
			if (entity->node[i][j].f < 99999 && entity->closed_list[i][j] == 0)
				return (1);
	}
	return (0);
}

void	free_lists(t_data *data, t_entity *entity)
{
	int	i;

	i = -1;
	while (++i < data->map.height)
	{
		free(entity->node[i]);
		free(entity->closed_list[i]);
	}
	free(entity->node);
	free(entity->closed_list);
	// free(entity);
}

void	init_lists(t_data *data, t_entity *entity)
{
	int	i;
	int	j;

	i = -1;
	entity->closed_list = malloc(sizeof(int *) * data->map.height);
	entity->node = malloc(sizeof(t_node *) * data->map.height);
	while (++i < data->map.height)
	{
		j = -1;
		entity->node[i] = malloc(sizeof(t_node) * ft_strlen(data->map.map[i]));
		entity->closed_list[i] = malloc(sizeof(int)
				* ft_strlen(data->map.map[i]));
		while (data->map.map[i][++j])
		{
			entity->closed_list[i][j] = 0;
			if (data->map.map[i][j] == '1' || data->map.map[i][j] == 'D')
				entity->closed_list[i][j] = 1;
			entity->node[i][j].f = 99999;
			entity->node[i][j].g = 99999;
			entity->node[i][j].h = 99999;
			entity->node[i][j].prev_x = -1;
			entity->node[i][j].prev_y = -1;
		}
	}
}

void	find_min_node(t_data *data, t_entity *entity, int *x, int *y)
{
	int	i;
	int	j;
	int	min_f;

	i = -1;
	min_f = 99999;
	while (++i < data->map.height)
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (entity->node[i][j].f < min_f && entity->closed_list[i][j] == 0)
			{
				min_f = entity->node[i][j].f;
				*x = j;
				*y = i;
			}
		}
	}
}

void	fill_node(t_data *data, t_entity *e, int x, int y)
{
	if (!e->closed_list[e->ny + y][e->nx + x])
	{
		e->node[e->ny + y][e->nx + x].g = 1;
		e->node[e->ny + y][e->nx + x].h = sqrt((data->player_x - e->nx + x)
				* (data->player_x - e->nx + x) + (data->player_y - (e->ny + y))
				* (data->player_y - (e->ny + y)));
		e->node[e->ny + y][e->nx + x].f = e->node[e->ny + y][e->nx + x].g
			+ e->node[e->ny + y][e->nx + x].h;
		e->node[e->ny + y][e->nx + x].prev_x = e->nx;
		e->node[e->ny + y][e->nx + x].prev_y = e->ny;
	}
}
