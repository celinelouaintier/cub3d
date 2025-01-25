/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:14:49 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/25 02:23:12 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_tex_x(t_data *data, double wallx)
{
    t_img      *textures;
    t_raycast   *raycast;
    int         tex_x;

    textures = &data->img;
    raycast = &data->raycast;
    tex_x = (int)(wallx * (double)textures->texwidth[set_tex_i(raycast)]);
    if ((!raycast->side && raycast->ray_dir_x > 0) || (raycast->side && raycast->ray_dir_y < 0))
        tex_x = textures->texwidth[set_tex_i(raycast)] - tex_x - 1;
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

    textures = &data->img;
    raycast = &data->raycast;
    step = 1.0 * textures->texheight[set_tex_i(raycast)] / raycast->line_height;
    tex_pos = (draw_start - HEIGHT / 2 + raycast->line_height / 2) * step;
    while (draw_start < draw_end)
    {
        tex_y = (int)tex_pos & (textures->texheight[set_tex_i(raycast)] - 1);
        tex_pos += step;
        color = textures->texaddr[set_tex_i(raycast)][tex_y * textures->texheight[set_tex_i(raycast)] + tex_x];
        put_pixel(&data->img, x, draw_start, color);
        draw_start++;
    }
}

void    apply_tex(t_data *data, int x, int draw_start, int draw_end)
{
    t_raycast   *raycast;
    double       wallx;
    int         tex_x;

    raycast = &data->raycast;
    if (!raycast->side)
        wallx = data->player_y + raycast->wall_dist * raycast->ray_dir_y;
    else
        wallx = data->player_x + raycast->wall_dist * raycast->ray_dir_x;
    wallx -= floor(wallx);
    tex_x = get_tex_x(data, wallx);
    wall_line(data, x, draw_start, draw_end, tex_x);
}
