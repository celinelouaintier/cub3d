/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/28 12:54:35 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	mouse_move(int x, int y, t_data *data)
// {
// 	int			delta_x;

// 	(void)y;
// 	if (x != WIDTH / 2)
// 	{
// 		delta_x = x - WIDTH / 2;
// 		data->angle -= delta_x * 0.001;
// 		if (data->angle < 0)
// 			data->angle += 2 * M_PI;
// 		if (data->angle > 2 * M_PI)
// 			data->angle -= 2 * M_PI;
// 		mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
// 	}
// 	return (0);
// }

// ------ PAS TOUCHE ------ //
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
	data->angle -= delta_x * 0.003;
	if (data->angle < 0)
		data->angle += 2 * M_PI;
	if (data->angle > 2 * M_PI)
		data->angle -= 2 * M_PI;
	data->last_x = x;
	return (0);
}

void	interact(t_data *data)
{
	if (data->map.map[(int)data->player_y][(int)data->player_x + 1] == 'D')
		data->map.map[(int)data->player_y][(int)data->player_x + 1] = 'O';
	else if (data->map.map[(int)data->player_y][(int)data->player_x - 1] == 'D')
		data->map.map[(int)data->player_y][(int)data->player_x - 1] = 'O';
	else if (data->map.map[(int)data->player_y + 1][(int)data->player_x] == 'D')
		data->map.map[(int)data->player_y + 1][(int)data->player_x] = 'O';
	else if (data->map.map[(int)data->player_y - 1][(int)data->player_x] == 'D')
		data->map.map[(int)data->player_y - 1][(int)data->player_x] = 'O';
	else if (data->map.map[(int)data->player_y][(int)data->player_x + 1] == 'O')
		data->map.map[(int)data->player_y][(int)data->player_x + 1] = 'D';
	else if (data->map.map[(int)data->player_y][(int)data->player_x - 1] == 'O')
		data->map.map[(int)data->player_y][(int)data->player_x - 1] = 'D';
	else if (data->map.map[(int)data->player_y + 1][(int)data->player_x] == 'O')
		data->map.map[(int)data->player_y + 1][(int)data->player_x] = 'D';
	else if (data->map.map[(int)data->player_y - 1][(int)data->player_x] == 'O')
		data->map.map[(int)data->player_y - 1][(int)data->player_x] = 'D';
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		finish_game(data);
	if (keycode == XK_Left)
		data->key.left = 1;
	if (keycode == XK_Right)
		data->key.right = 1;
	if (keycode == 'w')
		data->key.w = 1;
	if (keycode == 'a')
		data->key.a = 1;
	if (keycode == 's')
		data->key.s = 1;
	if (keycode == 'd')
		data->key.d = 1;
	if (keycode == 'e')
		interact(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 'w')
		data->key.w = 0;
	if (keycode == 'a')
		data->key.a = 0;
	if (keycode == 's')
		data->key.s = 0;
	if (keycode == 'd')
		data->key.d = 0;
	if (keycode == XK_Left)
		data->key.left = 0;
	if (keycode == XK_Right)
		data->key.right = 0;
	return (0);
}

void	camera_move(t_data *data)
{
	if (data->key.left)
		data->angle += 0.05;
	if (data->key.right)
		data->angle -= 0.05;
}

int	player_move(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (data->key.w)
	{
		new_x = data->player_x + data->raycast.dir_x * 0.1;
		new_y = data->player_y + data->raycast.dir_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] == '0' || data->map.map[(int)new_y][(int)new_x] == 'O')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->key.s)
	{
		new_x = data->player_x - data->raycast.dir_x * 0.1;
		new_y = data->player_y - data->raycast.dir_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] == '0' || data->map.map[(int)new_y][(int)new_x] == 'O')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->key.d)
	{
		new_x = data->player_x + data->raycast.plane_x * 0.1;
		new_y = data->player_y + data->raycast.plane_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] == '0' || data->map.map[(int)new_y][(int)new_x] == 'O')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->key.a)
	{
		new_x = data->player_x - data->raycast.plane_x * 0.1;
		new_y = data->player_y - data->raycast.plane_y * 0.1;
		if (data->map.map[(int)new_y][(int)new_x] == '0' || data->map.map[(int)new_y][(int)new_x] == 'O')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	return (0);
}
