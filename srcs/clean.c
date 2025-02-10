/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:40:03 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/10 15:35:43 by clouaint         ###   ########.fr       */
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

#include "mlx.h"

void	destroy_images(t_data *data)
{
	int i;

	if (!data || !data->mlx)
		return ;
	i = 0;
	while (i < 5)
	{
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx, data->tex[i].img);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (data->enemy[i].img)
			mlx_destroy_image(data->mlx, data->enemy[i].img);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (data->weapon[i].img)
			mlx_destroy_image(data->mlx, data->weapon[i].img);
		i++;
	}
	while (i < 2)
	{
		if (data->health[i].img)
			mlx_destroy_image(data->mlx, data->health[i].img);
		i++;
	}
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
}


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
	destroy_images(data);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map.map, data->map.height);
	free(data);
	exit(EXIT_SUCCESS);
}