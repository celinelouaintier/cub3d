/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/05 20:28:34 by clouaint         ###   ########.fr       */
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
				data->player_x = j;
				data->player_y = i;
				find_angle(data, i, j);
				data->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

// x = position horizontale de base de la souris sur la fenetre, c'est la mlx qui calcule ca
int	mouse_move(int x, int y, t_data *data)
{
	int			delta_x;

	(void)y;
	if (data->last_x == -1)
	{
		data->last_x = x;
		return (0);
	}
	delta_x = x - data->last_x;
	data->angle += delta_x * 0.003;
	if (data->angle < 0)
		data->angle -= 2 * M_PI;
	if (data->angle > 2 * M_PI)
		data->angle += 2 * M_PI;
	data->last_x = x;
	printf("Player angle: %f\n", data->angle);
	return (0);
}