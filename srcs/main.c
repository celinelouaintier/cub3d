/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:48 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/23 16:45:05 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	finish_game(t_data *game)
{
	mlx_destroy_window(game->mlx, game->window);
	// destroy_images(game);
	mlx_destroy_display(game->mlx);
	// free(game->mlx);
	// free_map(game->map, game->height);
	// free(game->images);
	exit(0);
}

int main(int ac, char **av)
{
    t_data  *data;
    int fd;

    data = malloc(sizeof(t_data));
	if (ac != 2)
		return (1);
	data->map.path = av[1];
    fd = open(data->map.path, O_RDONLY);
    init_texture(fd, &data->map);
    fill_map(fd, &data->map);
    data->mlx = mlx_init();
    if (!data->mlx)
        return (1);
    data->window = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
    mlx_hook(data->window, 17, 0, finish_game, data);
    // mlx_loop_hook(data->mlx, render_floor, data);
    mlx_loop(data->mlx);
    return (0);
}
