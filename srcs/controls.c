/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:52:43 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/10 16:01:56 by clouaint         ###   ########.fr       */
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

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx);
	if (keycode == XK_Left)
		data->key.left = 1;
	if (keycode == XK_Right)
		data->key.right = 1;
	if (keycode == XK_Shift_L)
		data->speed = 0.2;
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
	if (keycode == XK_Left)
		data->key.left = 0;
	if (keycode == XK_Right)
		data->key.right = 0;
	if (keycode == XK_Shift_L)
		data->speed = 0.1;
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

void	camera_move(t_data *data)
{
	if (data->key.left)
		data->angle += 0.05;
	if (data->key.right)
		data->angle -= 0.05;
}
