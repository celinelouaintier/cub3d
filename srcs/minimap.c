/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:08:00 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/29 14:29:04 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, int x, int y, int color, int cell)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell)
	{
		j = 0;
		while (j < cell)
		{
			put_pixel(&data->minimap, x + i, y + j, color);
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
			put_pixel(&data->minimap,px + i, py + j, get_color(data, "125,52,201"));
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
	int	cell;
	// int	max_dim;
	
	i = 0;
	j = 0;
	if (data->minimap.img)
	{
		mlx_destroy_image(data->mlx, data->minimap.img);
		data->minimap.img = mlx_new_image(data->mlx, 200, 200);
		data->minimap.addr = (int *)mlx_get_data_addr(data->minimap.img, &data->minimap.pixel_bits, &data->minimap.size_line, &data->minimap.endian);
	}
	cell = 200 / data->map.height;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == ' ')
    			color = get_color(data, "200,200,200");
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
			draw_square(data, j * cell, i * cell, color, cell);
			j++;
		}
		i++;
	}
}
