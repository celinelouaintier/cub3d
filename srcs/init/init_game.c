/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:44:59 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/02 22:55:11 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap(t_data *data)
{
	data->minimap.height = data->map.height * 20;
	data->minimap.width = data->map.width * 20;
	if (data->minimap.width > data->minimap.height)
	{
		if (data->minimap.width > MINIMAP_MAX)
		{
			data->minimap.width = MINIMAP_MAX;
			data->minimap.height = (data->map.height * MINIMAP_MAX)
				/ data->map.width;
		}
	}
	else
	{
		if (data->minimap.height > MINIMAP_MAX)
		{
			data->minimap.height = MINIMAP_MAX;
			data->minimap.width = (data->map.width * MINIMAP_MAX)
				/ data->map.height;
		}
	}	
	data->minimap.img = mlx_new_image(data->mlx,
			data->minimap.width, data->minimap.height);
	data->minimap.addr = (int *)mlx_get_data_addr(data->minimap.img,
			&data->minimap.pixel_bits, &data->minimap.size_line,
			&data->minimap.endian);
}

void	set_img(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = NULL;
	data->img.addr = NULL;
	data->img.pixel_bits = 0;
	data->img.size_line = 0;
	data->img.endian = 0;
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.pixel_bits, &data->img.size_line, &data->img.endian);
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
	init_minimap(data);
}

void	draw_bg(t_data *data)
{
	int	x;
	int	y;
	int	color;

	color = get_color(data, data->map.cell);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y > HEIGHT / 2)
			color = get_color(data, data->map.floor);
		while (x < WIDTH)
		{
			put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

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
				data->player_x = j + 0.5;
				data->player_y = i + 0.5;
				find_angle(data, i, j);
				data->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

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
	int k;

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
