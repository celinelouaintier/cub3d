/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:41:39 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/03 21:52:08 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_ennemy(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width)
			if (data->map.map[i][j] == 'X')
				data->nb_entity++;
	}
}

void	init_ennemy(t_data *data)
{
	int	i;
	int	j;
	int	k;

	if (!BONUS)
	{
		data->nb_entity = 0;
		return ;
	}
	count_ennemy(data);
	data->entity = malloc(sizeof(t_entity) * data->nb_entity);
	k = 0;
	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width)
		{
			if (data->map.map[i][j] == 'X')
			{
				data->entity[k].x = j + 0.5;
				data->entity[k].y = i + 0.5;
				data->entity[k].is_alive = 1;
				data->entity[k].targeted = 0;
				k++;
				if (k == data->nb_entity)
					return ;
			}
		}
	}
}
