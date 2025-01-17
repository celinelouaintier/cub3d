/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:46:41 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/10 13:47:29 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, char *str)
{
	int	r;
	int	g;
	int	b;
	int	color;

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

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return ;
	pixel = y * (image->size_line / 4) + x;
	// printf("size_line: %d, x: %d, y: %d, pixel index: %d\n", image->size_line, x, y, pixel);
	image->addr[pixel] = color;
}

void	draw_line(t_data *data, int start, int end, int x)
{
	while (start++ < end)
		put_pixel(&data->img, x, start, data->color);
}
