/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:48 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/24 02:39:27 by nferrad          ###   ########.fr       */
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
	if (keycode == 'd')
		data->startx -= 10;
	if (keycode == 'a')
		data->startx += 10;
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
	data->startx = WIDTH / 3;
	data->starty = HEIGHT / 3;
    if (!data->mlx)
        return (1);
    data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    // draw_square(data);
    mlx_hook(data->window, 17, 0, finish_game, data);
    mlx_hook(data->window, 2, 1L << 0, player_move, data);
    mlx_loop_hook(data->mlx, game_loop, data);
    mlx_loop(data->mlx);
    return (0);
}
