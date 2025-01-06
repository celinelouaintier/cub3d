/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/05 21:37:09 by clouaint         ###   ########.fr       */
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
	if (x != WIDTH / 2)
	{
		delta_x = x - WIDTH / 2;
		data->angle -= delta_x * 0.003;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		data->raycast.dir_x = cos(data->angle);
		data->raycast.dir_y = -sin(data->angle);
		data->raycast.plane_x = sin(data->angle) * 0.66;
		data->raycast.plane_y = cos(data->angle) * 0.66;
		// printf("Player angle: %f\n", data->angle);
		mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

int player_move(int keycode, t_data *data)
{
	if (keycode == 65307)
		finish_game(data);
	if (keycode == 'w')
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x + data->raycast.dir_x * 0.1)] != '1')
			data->player_x += data->raycast.dir_x * 0.1;
		if(data->map.map[(int)(data->player_y + data->raycast.dir_y * 0.1)][(int)data->player_x] != '1')
			data->player_y += data->raycast.dir_y * 0.1;
	}
	if (keycode == 's')
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x - data->raycast.dir_x * 0.1)] != '1')
			data->player_x -= data->raycast.dir_x * 0.1;
		if(data->map.map[(int)(data->player_y - data->raycast.dir_y * 0.1)][(int)data->player_x] != '1')
			data->player_y -= data->raycast.dir_y * 0.1;
	}
	if (keycode == 'd')
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x + data->raycast.plane_x * 0.1)] != '1')
			data->player_x += data->raycast.plane_x * 0.1;
		if(data->map.map[(int)(data->player_y + data->raycast.plane_y * 0.1)][(int)data->player_x] != '1')
			data->player_y += data->raycast.plane_y * 0.1;
	}
	if (keycode == 'a')
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x - data->raycast.plane_x * 0.1)] != '1')
			data->player_x -= data->raycast.plane_x * 0.1;
		if(data->map.map[(int)(data->player_y - data->raycast.plane_y * 0.1)][(int)data->player_x] != '1')
			data->player_y -= data->raycast.plane_y * 0.1;
	}
	// mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	return (0);
}