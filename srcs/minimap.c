/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:08:00 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/06 16:00:38 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, int x, int y, int cell)
{
	int	i;
	int	j;

	i = 0;
	(void)cell;
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

void	draw_head(t_data *data, int px, int py, int dir_x, int dir_y)
{
	int		steps;
	int		i;
	float	x;
	float	y;

	i = 0;
	if (abs(dir_x - px) > abs(dir_y - py))
		steps = abs(dir_x - px);
	else
		steps = abs(dir_y - py);
	x = px;
	y = py;
	while (i <= steps)
	{
		put_pixel(&data->minimap, (int)x, (int) y,
			get_color(data, "52,126,89"));
		x += (dir_x - px) / (float) steps;
		y += (dir_y - py) / (float) steps;
		i++;
	}
}

void	draw_player(t_data *data, int cell_w, int cell_h)
{
	int	px;
	int	py;
	int	p_size;
	// int	dir_x;
	// int	dir_y;
	px = data->player_x * cell_w;
	py = data->player_y * cell_h;
	p_size = cell_w / 2;
	if (p_size < 3)
		p_size = 3;
	data->minimap.color = get_color(data, "255,0,0");
	draw_square(data, px - p_size / 2, py - p_size / 2, p_size);
// 	dir_x = px + cos(data->angle) * (p_size * 2);
// 	dir_y = py + sin(data->angle) * (p_size * 2);
// 	draw_head(data, px, py, dir_x, dir_x);
}

void	render_minimap(t_data *data)
{
	int	i;
	int	j;
	int	cell_w;
	int	cell_h;

	i = -1;
	cell_w = data->minimap.width / data->map.width;
	cell_h = data->minimap.height / data->map.height;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width)
		{
			if (data->map.map[i][j] == '1')
				data->minimap.color = get_color(data, "99,57,116" );
			else if (data->map.map[i][j] == '0')
				data->minimap.color = get_color(data, "253,254,254");
			else if (data->map.map[i][j] == ' ')
				data->minimap.color = get_color(data, data->map.cell);
			draw_square(data, j * cell_w, i * cell_h, cell_w + 4);
		}
	}
	draw_player(data, cell_w, cell_h);
}
