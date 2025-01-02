/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/02 16:46:41 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_angle(t_data *data, int i, int j)
{
	if (data->map.map[i][j] == 'N')
		data->angle = M_PI / 2;
	else if (data->map.map[i][j] == 'S')
		data->angle = 3 * M_PI / 2;
	else if (data->map.map[i][j] == 'E')
		data->angle = 0;
	else if (data->map.map[i][j] == 'W')
		data->angle = M_PI;
}

void	find_initial_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' ||
				data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			{
				data->startx = j;
				data->starty = i;
				find_angle(data, i, j);
				data->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}
