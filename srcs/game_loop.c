/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/05 20:12:20 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->nb_entity)
		data->entity[i].distance = ((data->player_x - data->entity[i].x)
				* (data->player_x - data->entity[i].x) + (data->player_y
					- data->entity[i].y)
				* (data->player_y - data->entity[i].y));
	i = -1;
	while (++i < data->nb_entity)
	{
		j = -1;
		while (++j < data->nb_entity)
			if (data->entity[j].distance < data->entity[j + 1].distance)
				swap(&data->entity[j], &data->entity[j + 1]);
	}
}

void	raycast(t_data *data)
{
	int			x;
	int			draw_end = 0;
	int			draw_start = 0;
	int			i;
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

void	move_enemies(t_data *data)
{
	int		i;
	float	new_x;
	float	new_y;

	i = -1;
	while (++i < data->nb_entity)
	{
		new_x = data->entity[i].x;
		new_y = data->entity[i].y;
		if (data->entity[i].x > data->player_x)
			new_x = data->entity[i].x - 0.05;
		if (data->entity[i].x < data->player_x)
			new_x = data->entity[i].x + 0.05;
		if (data->entity[i].y > data->player_y)
			new_y = data->entity[i].y - 0.05;
		if (data->entity[i].y < data->player_y)
			new_y = data->entity[i].y + 0.05;
		if (data->map.map[(int)new_y][(int)new_x] != '1'
			&& data->map.map[(int)new_y][(int)new_x] != 'D')
		{
			data->entity[i].x = new_x;
			data->entity[i].y = new_y;
		}
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

int	game_loop(t_data *data)
{
	set_img(data);
	draw_bg(data);
	animate_player(data);
	if (data->shot)
		data->w_frame_count++;
	if (data->w_frame_count >= 5)
	{
		data->shot = 0;
		data->w_frame_count = 0;
	}
	camera_move(data);
	raycast(data);
	int i = 0;
	for (int x = 0; x < data->weapon[data->shot].height; x++)
	{
		for (int y = 0; y < data->weapon[data->shot].width; y++)
		{
			put_pixel(&data->img, (WIDTH / 2) + y + 100 , (HEIGHT / 2) + x , data->weapon[data->shot].addr[i]);
			i++;
		}
	}
	move_enemies(data);
	draw_cursor(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->minimap.img, 20, 20);
	player_move(data);
	return (0);
}
