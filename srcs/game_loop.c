/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/07 19:28:43 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_data *data)
{
	int			x;
	int			i;
	t_raycast	*raycast;

	x = -1;
	data->draw_start = 0;
	data->draw_end = 0;
	raycast = &data->raycast;
	init_ray_dir(data);
	while (++x < WIDTH)
	{
		init_raycast(raycast, data, x);
		set_step(data);
		raycast->side = check_ray_hit(raycast, data);
		draw_limits(raycast, &data->draw_start, &data->draw_end);
		apply_tex(data, x);
		data->sprite.wall_dist_buffer[x] = raycast->wall_dist;
	}
	sort_sprites(data);
	i = -1;
	while (++i < data->nb_entity)
	{
		if (!data->entity[i].is_alive)
			continue ;
		calculate_sprite_projection(data, raycast, i);
		set_draw_range(data);
		data->entity[i].targeted = 0;
		draw_sprite(data, i);
	}
}

void	draw_cursor(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 21)
	{
		j = -1;
		while (++j < 21)
			if ((i > 9 && i < 12) || (j > 9 && j < 12))
				put_pixel(&data->img, WIDTH / 2 + j,
					HEIGHT / 2 + i, 0x00FF0000);
	}
}

void	draw_weapon(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	if (data->shot)
		data->w_frame_count++;
	if (data->w_frame_count >= 5)
	{
		data->shot = 0;
		data->w_frame_count = 0;
	}
	while (x++ < data->weapon[data->shot].height)
	{
		y = 0;
		while (y++ < data->weapon[data->shot].width)
			put_pixel(&data->img, (WIDTH / 2) + y + 100,
				(HEIGHT / 2) + x, data->weapon[data->shot].addr[i++]);
	}
}

void	draw_health(t_data *data)
{
	int	i;
	int	x;
	int	y;
	int	width;

	i = 0;
	x = 0;
	while (x++ < data->health[0].height)
	{
		y = 0;
		while (y++ < data->health[0].width)
			put_pixel(&data->img, y + 50, x + (HEIGHT - 100),
				data->health[0].addr[i++]);
	}
	i = 0;
	x = 0;
	width = (data->hp * data->health[1].width) / data->hp_max;
	while (x++ < data->health[1].height)
	{
		y = 0;
		while (y++ < width)
			put_pixel(&data->img, y + 88, x + (HEIGHT - 88),
				data->health[1].addr[i++]);
		i += data->health[1].width - width;
	}
}

int	game_loop(t_data *data)
{
	set_img(data);
	draw_bg(data);
	animate_player(data);
	camera_move(data);
	raycast(data);
	enemies(data);
	draw_weapon(data);
	draw_cursor(data);
	draw_health(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->minimap.img, 20, 20);
	player_move(data);
	return (0);
}

// int tmp;
// while (x != (int)data->entity[0].x || y != (int)data->entity[0].y)
// {
	// 	if (data->node[y][x].prev_x == -1 && data->node[y][x].prev_y == -1)
	// 	{
	// 		tmp = data->entity[0].x;
	// 		y = data->entity[0].y;
	// 		x = tmp;
	// 	}
	// 	if (data->node[y][x].prev_x < x)
	// 		endX = drawX - 50;
	// 	if (data->node[y][x].prev_x > x)
	// 		endX = drawX + 50;
	// 	if (data->node[y][x].prev_y < y)
	// 		endY = drawY - 50;
	// 	if (data->node[y][x].prev_y > y)
	// 		endY = drawY + 50;
	// 	while (drawX != endX || drawY != endY)
	// 	{
		// 		put_pixel(&data->img, drawX, drawY, 0x00FF0000);
		// 		if (drawX < endX)
		// 			drawX++;
	// 		else if (drawX > endX)
	// 			drawX--;
	// 		if (drawY < endY)
	// 			drawY++;
	// 		else if (drawY > endY)
	// 			drawY--;
	// 	}
	// 	tmp = data->node[y][x].prev_x;
	// 	y = data->node[y][x].prev_y;
	// 	x = tmp;
	// 	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	// 	usleep(500000);
	// }