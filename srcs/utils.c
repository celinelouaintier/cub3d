/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:46:41 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/23 16:38:19 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_color(t_data *data, char *str)
{
    int r;
    int g;
    int b;
    int color;

    r = ft_atoi(str);
    str = ft_strchr(str, ',') + 1;
    g = ft_atoi(str);
    str = ft_strchr(str, ',') + 1;
    b = ft_atoi(str);
    color = (0 << 24 | r << 16 | g << 8 | b);
    return (mlx_get_color_value(data->mlx, color));
}

void	put_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}
