/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/04 21:10:10 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	raycast(t_data *data)
{
	int			x;
	int			side;
	int			draw_end;
	int			draw_start;
	t_raycast	*raycast;

	x = -1;
	raycast = &data->raycast;
	data->color = get_color(data, "233,128,9");
	raycast->dir_x = cos(data->angle);
	raycast->dir_y = -sin(data->angle);
	raycast->plane_x = sin(data->angle) * 0.66;
	raycast->plane_y = cos(data->angle) * 0.66;
	while (++x < WIDTH)
	{
		init_raycast(raycast, data, x);
		set_step(data);
		side = check_ray_hit(raycast, data);
		raycast->line_height = (int)(HEIGHT / raycast->perp_wall_dist);
		draw_start = -raycast->line_height / 2 + HEIGHT / 2;
		draw_end = raycast->line_height / 2 + HEIGHT / 2;
		data->color = get_color(data, "233,128,9"); // TMP
		if (side)
			data->color = get_color(data, "184, 125, 9"); // TMP
		draw_line(data, draw_start, draw_end, x);
	}
}

int	game_loop(t_data *data)
{
	set_img(data);
	draw_bg(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	return (0);
}

// creer un rectangle pour chaque 0 sur la map
// void    draw_cell(t_data *data, int x, int y, int color)
// {
//     int i;
//     int x;

//     i = 0;
//     while (i < data->map->height)
//     {
//         j = 0;
//         while (data->map->map[i][j])
//         {
//             mlx_pixel_put(data->mlx, data->window, x + j, y + i, color);
//             j++;
//         }
//         i++;
//     }    
// }

// int    render_floor(t_data *data, int size)
// {
//     int x;
//     int y;
//     int color;

//     color = get_color(data, data->map->floor);
//     y = 0;
//     while (y < data->map->height)
//     {
//         x = 0;
//         while (x < data->map->width)
//         {
//             if (data->map->map[y][x] == '0')
//                 draw_cell(data, x * size, y * size, color);
//             x++;
//         }
//         y++;
//     }
//     return (0);
// }

/*
void	draw_square(t_data *data)
{
	int	x;
	int	y;
	int z;
	int z2 = 0;
	int height, width, offset, color;
	t_img texture;

	y = 0;
	set_img(data);
	texture.img = mlx_xpm_file_to_image(data->mlx, "assets/cobblestone.xpm", &width, &height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.pixel_bits, &texture.size_line, &texture.endian);
	while (y < height)
	{
		x = 0;
		z = 0;
		while (x < width)
		{
			offset = y * texture.size_line + x * (texture.pixel_bits / 8);
			color = *(int *)(texture.addr + offset);
			while (z % 50)
			{
				put_pixel(&data->img, data->startx + x + z, data->starty + y + z2, color);
				z++;
			}
			z++;
			x++;
		}
		y++;
		z2++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
}
*/