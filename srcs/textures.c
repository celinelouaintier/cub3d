/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:14:49 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/13 17:17:16 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0 || color < 0)
		return ;
	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

int	get_tex_x(t_data *data, double wallx)
{
	t_img		*textures;
	t_raycast	*raycast;
	int			tex_x;

	raycast = &data->raycast;
	textures = &data->tex[set_tex_i(raycast)];
	tex_x = (int)(wallx * (double)textures->width);
	if ((!raycast->side && raycast->ray_dir_x > 0)
		|| (raycast->side && raycast->ray_dir_y < 0))
		tex_x = textures->width - tex_x - 1;
	return (tex_x);
}

void	wall_line(t_data *data, int x, int tex_x)
{
	t_img		*textures;
	t_raycast	*raycast;
	int			tex_y;
	double		tex_pos;
	double		step;

	raycast = &data->raycast;
	textures = &data->tex[set_tex_i(raycast)];
	step = 1.0 * textures->height / raycast->line_height;
	tex_pos = (data->draw_start - HEIGHT / 2 + raycast->line_height / 2) * step;
	while (data->draw_start < data->draw_end)
	{
		tex_y = (int)tex_pos & (textures->height - 1);
		tex_pos += step;
		data->img.color = textures->addr[tex_y * textures->height + tex_x];
		put_pixel(&data->img, x, data->draw_start, data->img.color);
		data->draw_start++;
	}
}

void	apply_tex(t_data *data, int x)
{
	t_raycast	*raycast;
	double		wallx;
	int			tex_x;

	raycast = &data->raycast;
	if (!raycast->side)
		wallx = data->player_y + raycast->wall_dist * raycast->ray_dir_y;
	else
		wallx = data->player_x + raycast->wall_dist * raycast->ray_dir_x;
	wallx -= floor(wallx);
	tex_x = get_tex_x(data, wallx);
	wall_line(data, x, tex_x);
}

int	have_door(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(data->map.map[i]))
		{
			if (data->map.map[i][j] == 'D')
				return (1);
		}
	}
	return (0);
}
