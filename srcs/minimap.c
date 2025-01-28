/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:08:00 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/28 18:51:22 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP)
	{
		j = 0;
		while (j < MINIMAP)
		{
			put_pixel(data->minimap.img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_data *data)
{
	int	i;
	int	j;
	int color;
	
	i = 0;
	printf("height : %d, width : %d \n", data->map.height, data->map.width);
	while (i < data->map.height)
	{
		if (data->map.map == NULL || data->map.map[i] == NULL)
		{
    		printf("Error: map[%d] is NULL\n", i);
    		return;
		}
		j = 0;
		while (j < data->map.width)
		{
			if (j >= (int)ft_strlen(data->map.map[i]))
			{
    			printf("Error: map[%d][%d] is out of bounds\n", i, j);
    			return;
			}
    		printf("Processing map[%d][%d]: %c\n", i, j, data->map.map[i][j]);
			if (data->map.map[i][j] == ' ')
    			color = get_color(data, "200,200,200"); // Griser les zones vides
			else if (data->map.map[i][j] == '1')
				color = get_color(data, "0,0,0");
			else if (data->map.map[i][j] == '0')
				color = get_color(data, "255,255,255");
			else if (data->map.map[i][j] == 'D')
				color = get_color(data, "0,255,0");
			else if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' || data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
				color = get_color(data, "255,0,0");
			else
				color = get_color(data, "0,0,255");
			draw_square(data, j, i, color);
			j++;
		}
		i++;
	}
}
