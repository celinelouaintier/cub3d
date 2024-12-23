/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/23 18:45:08 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_square(t_data *data)
{
    int i;
    int j;

    i = 0;
    int x = 1920 / 3;
    int y = 1080 / 3;
    // int xs = 10;
    // int ys = 10;
    // data->wall = mlx_xpm_file_to_image(data->mlx, data->map.no, &xs, &ys);
    while (i < data->map.height * data->zoom)
    {
        j = 0;
        while (j < data->map.width * data->zoom)
        {
            put_pixel(&data->img, x + j, y + i, get_color(data, data->map.floor));
            j++;
        }
        i++;
    }   
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
}

int    game_loop(t_data *data)
{
    draw_square(data);
    return (0);
}


// creer un rectangle pour chaque 0 sur la map
// void    draw_cell(t_data *data, int x, int y, int color)
// {
//     int i;
//     int j;

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
