/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:48 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/03 18:13:42 by clouaint         ###   ########.fr       */
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

void	animate_player(t_data *data)
{
	data->frame_count++;
	if (data->frame_count >= 7)
	{
		data->current_sprite = (data->current_sprite + 1) % 6;
		data->frame_count = 0;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	check_file_format(av[1]);
	data = malloc(sizeof(t_data));
	if (ac != 2)
		return (1);
	data->map.path = av[1];
	if ((fd = open(data->map.path, O_RDONLY)) < 0)
		return (1);
	init_texture(fd, &data->map);
	fill_map(fd, &data->map);
	find_initial_position(data);
	init_ennemy(data);
	data->mlx = mlx_init();
	data->last_x = -1;
	if (!data->mlx)
		return (1);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	load_textures(data, data->map.no);
	load_textures(data, data->map.so);
	load_textures(data, data->map.ea);
	load_textures(data, data->map.we);
	if (BONUS)
	{
		load_textures(data, data->map.door);
		load_enemy(data);
		load_textures(data, "assets/weapon/DEAG1.xpm");
	}
	mlx_mouse_hide(data->mlx, data->window);
	mlx_hook(data->window, 17, 0, finish_game, data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 3, 1L << 1, key_release, data);
	if (BONUS)
	{
		mlx_hook(data->window, 6, 1L << 6, mouse_move, data);
		mlx_hook(data->window, 4, 1L << 2, shot, data);
	}
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
	return (0);
}
