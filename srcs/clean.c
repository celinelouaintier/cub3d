/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:40:03 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/13 15:16:58 by clouaint         ###   ########.fr       */
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

void	destroy_images(t_data *data)
{
	int	i;

	if (!data || !data->mlx)
		return ;
	i = -1;
	while (++i < 4 + BONUS)
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx, data->tex[i].img);
	if (BONUS)
	{
		i = -1;
		while (++i < 6)
			if (data->enemy[i].img)
				mlx_destroy_image(data->mlx, data->enemy[i].img);
		i = -1;
		while (++i < 5)
			if (data->weapon[i].img)
				mlx_destroy_image(data->mlx, data->weapon[i].img);
		i = -1;
		while (++i < 2)
			if (data->health[i].img)
				mlx_destroy_image(data->mlx, data->health[i].img);
	}
}

int	exit_game(t_data *data)
{
	if (data)
	{
		if (data->map.map)
			free_map(data->map.map, data->map.height);
		if (BONUS && data->map.door)
			free(data->map.door);
		if (data->map.no)
			free(data->map.no);
		if (data->map.so)
			free(data->map.so);
		if (data->map.ea)
			free(data->map.ea);
		if (data->map.floor)
			free(data->map.floor);
		if (data->map.cell)
			free(data->map.cell);
		if (data->map.we)
			free(data->map.we);
		free(data);
	}
	exit(EXIT_FAILURE);
}

void	finish_game(t_data *data)
{
	destroy_images(data);
	if (BONUS)
		free(data->entity);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit_game(data);
}

void	check_nb_value(t_data *data, int fd, int i, int nb_value)
{
	if (i != nb_value)
	{
		ft_printf("Error\nMissing texture\n");
		close(fd);
		exit_game(data);
	}
}
