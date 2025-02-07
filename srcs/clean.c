/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:40:03 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/07 20:24:14 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map, int height)
{
	int	i;
	
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// void	destroy_images(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (!data || !data->img. )
// }

int	exit_game(t_data *data)
{
	// if (data->window)
	// 	mlx_destroy_window(data->mlx, data->window);
	// free(data->mlx);
	if (data)
	{
		free_map(data->map.map, data->map.height);
		if (BONUS)
			free(data->map.door);
		free(data->map.no);
		free(data->map.so);
		free(data->map.ea);
		free(data->map.floor);
		free(data->map.cell);
		free(data->map.we);
		free(data);
	}
	exit(EXIT_FAILURE);
}

int	finish_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	// destroy_images(game);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map.map, data->map.height);
	free(data->img.img);
	free(data);
	exit(EXIT_SUCCESS);
}