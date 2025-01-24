/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:46:17 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/25 02:24:31 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void    load_textures(t_data *data)
// {
//     int i;
//     char *tab[5];

//     i = 0;
//     tab[0] = data->map.no;
//     tab[1] = data->map.so;
//     tab[2] = data->map.we;
//     tab[3] = data->map.ea;
//     if (BONUS)
//         tab[4] = data->map.door;
//     while (i < 4)
//     {
//         data->tex[i] = malloc(sizeof(t_img));
//         if (!data->tex[i])
//         {
//             ft_printf("Error: Memory allocation failed for texture %d\n", i);
//             exit(1);
//         }
//         data->tex[i]->endian = 0;
//         data->tex[i]->pixel_bits = 0;
//         data->tex[i]->size_line = 0;
//         data->tex[i]->img = mlx_xpm_file_to_image(data->mlx, tab[i], &data->tex[i]->width, &data->tex[i]->height);
//         if (!data->tex[i]->img)
//         {
//             ft_printf("Error: Failed to load texture: %s\n", tab[i]);
//             exit(1);
//         }
//         data->tex[i]->addr = (int *)mlx_get_data_addr(data->tex[i]->img, &data->tex[i]->pixel_bits, &data->tex[i]->size_line, &data->tex[i]->endian);
//         if (!data->tex[i]->addr)
//         {
//             ft_printf("Error: Failed to get data address for texture %d\n", i);
//             exit(1);
//         }
//         i++;
//     }
// }

void    load_textures(t_data *data, char *path)
{
	static int i = 0;

    if (path == NULL) 
    {
        perror("Texture path is NULL");
        finish_game(data);
    }
    data->img.tex[i] = mlx_xpm_file_to_image(data->mlx, path, &data->img.texwidth[i], &data->img.texheight[i]);
    if (!data->img.tex[i])
    {
        perror("failes to load texture\n");
        finish_game(data);
    }
    if (data->img.texwidth[i] <= 0 || data->img.texheight[i] <= 0)
    {
        perror("Invalid texture dimension\n");
        finish_game(data);
    }
    data->img.texaddr[i] = (int *)mlx_get_data_addr(data->img.tex[i], &data->img.pixel_bits, &data->img.size_line, &data->img.endian);
    if (!data->img.texaddr[i])
    {
        perror("Failed to get image address\n");
        finish_game(data);
    }
	i++;
}

int set_tex_i(t_raycast *raycast)
{
    if (raycast->side && raycast->step_y == -1) // NORTH
		return 0;
	else if (raycast->side && raycast->step_y == 1) // SOUTH
		return 1;
	else if (!raycast->side && raycast->step_x == 1) // EAST
		return 2;
	else if (!raycast->side && raycast->step_x == -1) // WEST
		return 3;
    return -1;
}

// void    draw_tex(t_data *data, double width, int draw_start, int draw_end, int tex_x, int x)
// {
//     double  step;
//     double  tex_pos;
//     int     tex_y;
//     int     height;
//     int     color;

//     step = 1.0 * width / data->raycast.line_height;
//     height = data->tex[set_tex_i(data)]->height;
//     tex_pos = (draw_start - HEIGHT / 2 + data->raycast.line_height / 2) * step;
//     while (draw_start < draw_end)
//     {
//         tex_y = (int)tex_pos & (height - 1);
//         tex_pos += step;
//         color = data->tex[set_tex_i(data)]->addr[height * tex_y + tex_x];
//         put_pixel(&data->img, x, draw_start, color);
//         draw_start++;
//     }
// }

// void    apply_tex(t_data *data, int draw_start, int draw_end, int x)
// {
//     // int     tex_num;
//     double  wallx;
//     int     tex_x;
//     double  width;

//     width = data->tex[set_tex_i(data)]->width;
//     // tex_num = data->map.map[data->raycast.map_x][data->raycast.map_y] - 1;
//     if (data->raycast.side == 0)
//         wallx = data->player_y + data->raycast.wall_dist * data->raycast.ray_dir_y;
//     else
//         wallx = data->player_x + data->raycast.wall_dist * data->raycast.ray_dir_x;
//     wallx -= floor(wallx);
//     tex_x = (int)(wallx * width);
//     if (!data->raycast.side && data->raycast.ray_dir_x > 0)
//         tex_x = width - tex_x - 1;
//     if (data->raycast.side && data->raycast.ray_dir_x < 0)
//         tex_x = width - tex_x - 1;
//     draw_tex(data, width, draw_start, draw_end, tex_x, x);
// }