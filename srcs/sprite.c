/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:25:40 by nferrad           #+#    #+#             */
/*   Updated: 2025/02/03 01:28:40 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_sprite_projection(t_data *data, t_raycast *raycast, int i)
{
	data->sprite.sprite_x = data->entity[i].x - data->player_x;
	data->sprite.sprite_y = data->entity[i].y - data->player_y;
	data->sprite.inv_det = 1.0 / (raycast->plane_x * raycast->dir_y
			- raycast->dir_x * raycast->plane_y);
	data->sprite.transform_x = data->sprite.inv_det * (raycast->dir_y
			* data->sprite.sprite_x - raycast->dir_x * data->sprite.sprite_y);
	data->sprite.transform_y = data->sprite.inv_det * (-raycast->plane_y
			* data->sprite.sprite_x + raycast->plane_x * data->sprite.sprite_y);
	data->sprite.screen_x = (int)((WIDTH / 2)
			* (1 + data->sprite.transform_x / data->sprite.transform_y));
	data->sprite.sprite_height = abs((int)(HEIGHT
				/ (data->sprite.transform_y)));
	data->sprite.sprite_width = abs((int)(HEIGHT / (data->sprite.transform_y)));
}

void	set_draw_range(t_data *data)
{
	data->sprite.draw_start_y = -data->sprite.sprite_height / 2 + HEIGHT / 2;
	if (data->sprite.draw_start_y < 0)
		data->sprite.draw_start_y = 0;
	data->sprite.draw_end_y = data->sprite.sprite_height / 2 + HEIGHT / 2;
	if (data->sprite.draw_end_y >= HEIGHT)
		data->sprite.draw_end_y = HEIGHT - 1;
	data->sprite.draw_start_x = -data->sprite.sprite_width
		/ 2 + data->sprite.screen_x;
	if (data->sprite.draw_start_x < 0)
		data->sprite.draw_start_x = 0;
	data->sprite.draw_end_x = data->sprite.sprite_width
		/ 2 + data->sprite.screen_x;
	if (data->sprite.draw_end_x >= WIDTH)
		data->sprite.draw_end_x = WIDTH - 1;
}

void	draw_sprite_line(t_data *data, int i, int tex_x, int stripe)
{
	int		tex_y;
	int		y;
	int		d;

	y = data->sprite.draw_start_y;
	while (y++ < data->sprite.draw_end_y)
	{
		d = y * 256 - HEIGHT * 128 + data->sprite.sprite_height * 128;
		tex_y = ((d * data->tex[5].height) / data->sprite.sprite_height) / 256;
		data->img.color = data->tex[5].addr[data->tex[5].width * tex_y + tex_x];
		if (data->img.color)
		{
			put_pixel(&data->img, stripe, y, data->img.color);
			if (stripe == WIDTH / 2)
				data->entity[i].targeted = 1;
		}
	}
}

void	draw_sprite(t_data *data, int i)
{
	int			tex_x;
	int			stripe;
	t_sprite	*s;

	stripe = data->sprite.draw_start_x;
	s = &data->sprite;
	while (stripe++ < s->draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-s->sprite_width
						/ 2 + s->screen_x)) * data->tex[5].width
				/ s->sprite_width) / 256;
		if (s->transform_y > 0 && stripe > 0 && stripe < WIDTH
			&& s->transform_y < s->wall_dist_buffer[stripe])
			draw_sprite_line(data, i, tex_x, stripe);
	}
}
