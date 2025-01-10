/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:38 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/10 14:53:51 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// x = position horizontale de base de la souris sur la fenetre, c'est la mlx qui calcule ca
int	mouse_move(int x, int y, t_data *data)
{
	int			delta_x;

	(void)y;
	if (x != WIDTH / 2)
	{
		delta_x = x - WIDTH / 2;
		data->angle -= delta_x * 0.001;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

// ------ PAS TOUCHE ------ //
// int	mouse_move(int x, int y, t_data *data)
// {
// 	int			delta_x;

// 	(void)y;
// 	if (data->last_x == -1)
// 	{
// 		data->last_x = x;
// 		return (0);
// 	}
// 	delta_x = x - data->last_x;
// 	data->angle -= delta_x * 0.003;
// 	if (data->angle < 0)
// 		data->angle += 2 * M_PI;
// 	if (data->angle > 2 * M_PI)
// 		data->angle -= 2 * M_PI;
// 	data->last_x = x;
// 	return (0);
// }

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		finish_game(data);
	if (keycode == 'w')
		data->key.w = 1;
	if (keycode == 'a')
		data->key.a = 1;
	if (keycode == 's')
		data->key.s = 1;
	if (keycode == 'd')
		data->key.d = 1;
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
	return (0);
}

int player_move(t_data *data)
{
	
	if (data->key.w)
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x + data->raycast.dir_x * 0.1)] != '1')
			data->player_x += data->raycast.dir_x * 0.1;
		if(data->map.map[(int)(data->player_y + data->raycast.dir_y * 0.1)][(int)data->player_x] != '1')
			data->player_y += data->raycast.dir_y * 0.1;
	}
	if (data->key.s)
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x - data->raycast.dir_x * 0.1)] != '1')
			data->player_x -= data->raycast.dir_x * 0.1;
		if(data->map.map[(int)(data->player_y - data->raycast.dir_y * 0.1)][(int)data->player_x] != '1')
			data->player_y -= data->raycast.dir_y * 0.1;
	}
	if (data->key.d)
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x + data->raycast.plane_x * 0.1)] != '1')
			data->player_x += data->raycast.plane_x * 0.1;
		if(data->map.map[(int)(data->player_y + data->raycast.plane_y * 0.1)][(int)data->player_x] != '1')
			data->player_y += data->raycast.plane_y * 0.1;
	}
	if (data->key.a)
	{
		if(data->map.map[(int)data->player_y][(int)(data->player_x - data->raycast.plane_x * 0.1)] != '1')
			data->player_x -= data->raycast.plane_x * 0.1;
		if(data->map.map[(int)(data->player_y - data->raycast.plane_y * 0.1)][(int)data->player_x] != '1')
			data->player_y -= data->raycast.plane_y * 0.1;
	}
	// mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	return (0);
}