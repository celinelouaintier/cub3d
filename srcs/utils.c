/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:46:41 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/13 17:19:50 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clamp_color(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

int	get_color(t_data *data, char *str)
{
	int		r;
	int		g;
	int		b;
	int		color;
	char	*comma;

	if (!str)
		return (0);
	r = clamp_color(ft_atoi(str));
	comma = ft_strchr(str, ',');
	if (!comma)
		return (0);
	str = comma + 1;
	g = clamp_color(ft_atoi(str));
	comma = ft_strchr(str, ',');
	if (!comma)
		return (0);
	str = comma + 1;
	b = clamp_color(ft_atoi(str));
	color = (r << 16 | g << 8 | b);
	return (mlx_get_color_value(data->mlx, color));
}

void	iswap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	fswap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	find_angle(t_data *data, int i, int j)
{
	if (data->map.map[i][j] == 'N')
		data->angle = M_PI / 2;
	else if (data->map.map[i][j] == 'S')
		data->angle = 3 * M_PI / 2;
	else if (data->map.map[i][j] == 'E')
		data->angle = 0;
	else if (data->map.map[i][j] == 'W')
		data->angle = M_PI;
}
