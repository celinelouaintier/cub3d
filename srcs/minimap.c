/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:08:00 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/29 17:43:43 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, int x, int y, int cell)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell)
	{
		j = 0;
		while (j < cell)
		{
			put_pixel(&data->minimap, x + i, y + j, data->minimap.color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data, int cell)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = (int)(data->player_x * cell / 64.0);
	py = (int)(data->player_y * cell / 64.0);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(&data->minimap, px + i, py + j,
				get_color(data, "231,76,60"));
			j++;
		}
		i++;
	}
}

void	render_minimap(t_data *data)
{
	int	i;
	int	j;
	int	cell_w;
	int	cell_h;

	i = 0;
	cell_w = data->minimap.width / data->map.width;
	cell_h = data->minimap.height / data->map.height;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == '1')
				data->minimap.color = get_color(data, "99,57,116" );
			else if (data->map.map[i][j] == '0')
				data->minimap.color = get_color(data, "253,254,254");
			else
				data->minimap.color = get_color(data, "0,0,0");
			draw_square(data, j * cell_w, i * cell_h, cell_w);
			j++;
		}
		i++;
	}
	// draw_player(data, cell);
}
