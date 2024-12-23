/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:53 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/23 16:32:29 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
