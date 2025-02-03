/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:46:41 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/02 22:15:10 by nferrad          ###   ########.fr       */
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

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0 || color < 0)
		return ;
	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	draw_line(t_data *data, int start, int end, int x)
{
	while (start++ < end)
		put_pixel(&data->img, x, start, data->img.color);
}

void	swap(t_entity *a, t_entity *b)
{
	t_entity	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}