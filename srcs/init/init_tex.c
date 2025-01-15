/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:46:17 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/15 16:57:02 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_textures(t_data *data, char *path, int i)
{
    if (path == NULL) 
    {
        perror("Texture path is NULL");
        finish_game(data);
    }
    data->img.tex[i] = mlx_xpm_file_to_image(data->mlx, path, &data->img.texwidth, &data->img.texheight);
    if (!data->img.tex[i])
    {
        perror("Failed to load texture\n");
        finish_game(data);
    }
    if (data->img.texwidth <= 0 || data->img.texheight <= 0)
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
}

void    load_textures(t_data *data)
{
    get_textures(data, data->map.no, 0);
    if (BONUS)
        get_textures(data, data->map.door, 1);
}