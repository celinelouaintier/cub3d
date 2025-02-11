/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:41:39 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/11 12:34:59 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_ennemy(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->nb_entity = 0;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(data->map.map[i]))
			if (data->map.map[i][j] == 'X')
				data->nb_entity++;
	}
}

void	init_ennemy(t_data *data)
{
	int	i;
	int	j;
	int	k;

	count_ennemy(data);
	data->entity = malloc(sizeof(t_entity) * data->nb_entity);
	if (!data->entity)
		exit_game(data);
	k = 0;
	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(data->map.map[i]))
		{
			if (data->map.map[i][j] == 'X')
			{
				data->entity[k].x = j + 0.5;
				data->entity[k].y = i + 0.5;
				data->entity[k].is_alive = 1;
				data->entity[k].targeted = 0;
				k++;
			}
		}
	}
}

void	init_entity(t_data *data)
{
	int	i;

	i = -1;
	sort_sprites(data);
	while (++i < data->nb_entity)
	{
		if (!data->entity[i].is_alive)
			continue ;
		calculate_sprite_projection(data, &data->raycast, i);
		set_draw_range(data);
		data->entity[i].targeted = 0;
		draw_sprite(data, i);
	}
}
