/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:08:00 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/11 13:12:19 by clouaint         ###   ########.fr       */
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

void	draw_player(t_data *data, int cell_w, int cell_h)
{
	int	px;
	int	py;
	int	p_size;

	px = data->player_x * cell_w;
	py = data->player_y * cell_h;
	p_size = cell_w / 2;
	if (p_size < 3)
		p_size = 3;
	data->minimap.color = get_color(data, "255,0,0");
	draw_square(data, px - p_size / 2, py - p_size / 2, p_size);
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
		while (++j < (int)ft_strlen(data->map.map[i]))
		{
			if (data->map.map[i][j] == '1')
				data->minimap.color = get_color(data, "99,57,116" );
			else if (data->map.map[i][j] == '0')
				data->minimap.color = get_color(data, "253,254,254");
			else if (data->map.map[i][j] == 'D')
				data->minimap.color = get_color(data, "65,189,126");
			else if (data->map.map[i][j] == ' ')
				data->minimap.color = get_color(data, data->map.cell);
			draw_square(data, j * cell_w, i * cell_h, cell_w + 4);
		}
	}
	draw_player(data, cell_w, cell_h);
}
