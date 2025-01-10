/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:14:49 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/10 14:54:39 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    load_textures(t_data *data)
{
    if (data->map.no == NULL) 
    {
        perror("Texture path is NULL");
        finish_game(data);
    }
    data->img.tex = mlx_xpm_file_to_image(data->mlx, data->map.no, &data->img.texwidth, &data->img.texheight);
    if (!data->img.tex)
    {
        perror("failes to load texture\n");
        finish_game(data);
    }
    if (data->img.texwidth <= 0 || data->img.texheight <= 0)
    {
        perror("Invalid texture dimension\n");
        finish_game(data);
    }
    data->img.texaddr = (int *)mlx_get_data_addr(data->img.tex, &data->img.pixel_bits, &data->img.size_line, &data->img.endian);
    if (!data->img.texaddr)
    {
        perror("Failed to get image address\n");
        finish_game(data);
    }
}

int get_tex_x(t_data *data, float wallx)
{
    t_img       *textures;
    t_raycast   *raycast;
    int         tex_x;

    textures = &data->img;
    raycast = &data->raycast;
    tex_x = (int)(wallx * (float)textures->texwidth);
    if ((raycast->side == 0 && raycast->ray_dir_x > 0) || (raycast->side == 1 && raycast->ray_dir_y < 0))
        tex_x = textures->texwidth - tex_x - 1;
    return (tex_x);
}

void    wall_line(t_data *data, int x, int draw_start, int draw_end, int tex_x)
{
    t_img       *textures;
    t_raycast   *raycast;
    int         tex_y;      
    double      tex_pos;
    double      step;
    int         color;
    int         y;

    textures = &data->img;
    raycast = &data->raycast;
    y = draw_start;
    step = 1.0 * textures->texheight / raycast->line_height;
    tex_pos = (y - HEIGHT / 2 + raycast->line_height / 2) * step;
    while (y < draw_end)
    {
        tex_y = (int)tex_pos & (textures->texheight - 1);
        tex_pos += step;
        color = textures->texaddr[tex_y * textures->texwidth + tex_x];
        put_pixel(&data->img, x, y, color);
        y++;
    }
}

void    apply_tex(t_data *data, int x, int draw_start, int draw_end)
{
    // t_img       *textures;
    t_raycast   *raycast;
    float       wallx;
    int         tex_x;

    raycast = &data->raycast;
    // textures = &data->img;
    if (raycast->side == 0)
        wallx = data->player_y + raycast->wall_dist * raycast->ray_dir_y;
    else
        wallx = data->player_x + raycast->wall_dist * raycast->ray_dir_x;
    wallx -=floor(wallx);
    tex_x = get_tex_x(data, wallx);
    wall_line(data, x, draw_start, draw_end, tex_x);
}
