/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/28 13:09:36 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_data *data)
{
	int			x;
	int			draw_end = 0;
	int			draw_start = 0;
	t_raycast	*raycast;

	x = -1;
	raycast = &data->raycast;
	init_ray_dir(data);
	while (++x < WIDTH)
	{
		init_raycast(raycast, data, x);
		set_step(data);
		raycast->side = check_ray_hit(raycast, data);
		draw_limits(raycast, &draw_start, &draw_end);
		apply_tex(data, x, draw_start, draw_end);
	}
}

int	game_loop(t_data *data)
{
	set_img(data);
	draw_bg(data);
	camera_move(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	player_move(data);
	return (0);
}
