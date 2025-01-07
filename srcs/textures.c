/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:14:49 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/07 15:58:50 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = NULL;
	data->img.addr = NULL;
	data->img.pixel_bits = 0;
	data->img.size_line = 0;
	data->img.endian = 0;
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.pixel_bits, &data->img.size_line, &data->img.endian);
}

void    load_textures(t_data *data)
{
    if (data->map.no == NULL) 
    {
        perror("Texture path is NULL");
        finish_game(data);
    }
    data->img.img = mlx_xpm_file_to_image(data->mlx, data->map.no, &data->img.width, &data->img.height);
    if (!data->img.img)
    {
        perror("failes to load texture\n");
        finish_game(data);
    }
    if (data->img.width <= 0 || data->img.height <= 0)
    {
        perror("Invalid texture dimension\n");
        finish_game(data);
    }
    data->img.addr = (int *)mlx_get_data_addr(data->img.img, &data->img.pixel_bits, &data->img.size_line, &data->img.endian);
    if (!data->img.addr)
    {
        perror("Failed to get image address\n");
        finish_game(data);
    }
    printf("Texture loaded successfully: %s, width: %d, height: %d\n", data->map.no, data->img.width, data->img.height);
}

// int get_tex_x(t_data *data, float wallx)
// {
//     t_img       *textures;
//     t_raycast   *raycast;
//     int         tex_x;

//     textures = &data->img;
//     raycast = &data->raycast;
//     tex_x = (int)(wallx * (float)textures->width);
//     if ((raycast->side == 0 && raycast->ray_dir_x > 0) || (raycast->side == 1 && raycast->ray_dir_y < 0))
//         tex_x = textures->width - tex_x - 1;
//     return (tex_x);
// }

// void    wall_line(t_data *data, int x, int y, int draw_end, int tex_x)
// {
//     t_img       *textures;
//     t_raycast   *raycast;
//     int         d;
//     int         tex_y;
//     int         color;

//     textures = &data->img;
//     raycast = &data->raycast;
//     if (y < 0)
//         y = 0;
//     if (y >= HEIGHT)
//         y = HEIGHT - 1;
//     while (y < draw_end)
//     {
//         d = y * HEIGHT * 128 + raycast->line_height * 128;
//         tex_y = ((d * textures->height) / raycast->line_height) / 256;
//         color = textures->addr[tex_y * textures->width + tex_x];
//         if (y >= 0 && y < HEIGHT)
//             data->img.addr[y * WIDTH + x] = color;
//         y++;
//     }
// }

// void    apply_tex(t_data *data, int x, int draw_start, int draw_end)
// {
//     t_img       *textures;
//     t_raycast   *raycast;
//     float       wallx;
//     int         tex_x;

//     raycast = &data->raycast;
//     textures = &data->img;
//     if (raycast->side == 0)
//         wallx = data->player_y + raycast->perp_wall_dist * raycast->ray_dir_y;
//     else
//         wallx = data->player_x + raycast->perp_wall_dist * raycast->ray_dir_x;
//     wallx -=floor(wallx);
//     tex_x = get_tex_x(data, wallx);
//     wall_line(data, x, draw_start, draw_end, tex_x);   
// }
