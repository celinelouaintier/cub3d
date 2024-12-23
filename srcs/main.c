/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:48 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/23 18:52:44 by clouaint         ###   ########.fr       */
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

int player_move(int keycode, t_data *data)
{
    if (keycode == 65307)
		finish_game(data);
    if (keycode == 's')
        data->zoom--;
    if (keycode == 'w')
        data->zoom++;
    return (0);
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
    data->zoom = 10;
    if (!data->mlx)
        return (1);
    data->window = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
    data->img.img = mlx_new_image(data->mlx, 1920, 1080);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img, &data->img.pixel_bits, &data->img.size_line,
			&data->img.endian);
    // draw_square(data);
    mlx_hook(data->window, 17, 0, finish_game, data);
    mlx_hook(data->window, 2, 1L << 0, player_move, data);
    mlx_loop_hook(data->mlx, game_loop, data);
    mlx_loop(data->mlx);
    return (0);
}
