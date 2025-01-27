/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/27 14:02:04 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_data *data)
{
	int			x;
	// int			side;
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
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	camera_move(data);
	player_move(data);
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