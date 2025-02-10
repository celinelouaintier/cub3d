/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:48 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/10 16:05:39 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	animate_player(t_data *data)
{
	data->p_frame_count = 0;
	data->p_frame_count++;
	if (data->p_frame_count >= 7)
	{
		data->current_sprite = (data->current_sprite + 1) % 6;
		data->p_frame_count = 0;
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
	check_errors(data);
	find_initial_position(data);
	init_ennemy(data);
	data->mlx = mlx_init();
	data->last_x = -1;
	data->speed = 0.1;
	data->hp_max = 100;
	data->hp = data->hp_max;
	init_key(data);
	if (!data->mlx)
		return (1);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	load_textures(data);
	mlx_mouse_hide(data->mlx, data->window);
	mlx_hook(data->window, 17, 0, mlx_loop_end, data->mlx);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 3, 1L << 1, key_release, data);
	if (BONUS)
	{
		mlx_hook(data->window, 6, 1L << 6, mouse_move, data);
		mlx_hook(data->window, 4, 1L << 2, shot, data);
	}
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
	finish_game(data);
	return (0);
}

// set_img(data);

// int starty = 100;
// int color;
// int step = 50;
// int EDrawx;
// int EDrawy;
// for(int i = 0; i < data->map.height; i++)
// {
// 	int startx = 100;
// 	for (int j = 0; data->map.map[i][j]; j++)
// 	{
// 		if (data->map.map[i][j] == '1')
// 			color = 0x00FF0000;
// 		else
// 			color = 0xFFFFFFF;
// 		if (data->map.map[i][j] == 'X')
// 		{
// 			Ex = j;
// 			Ey = i;
// 			put_pixel(&data->img, startx + step / 2, starty + step / 2, 0x000FF00);
// 		}
// 		if (data->map.map[i][j] == 'N')
// 		{
// 			EDrawx = startx + step / 2;
// 			EDrawy = starty + step / 2;
// 			put_pixel(&data->img, startx + step / 2, starty + step / 2, 0x000FFFF);
// 		}
// 		for (int k = 0; k < step; k++)
// 		{
// 			if (data->map.map[i][j] == '1' || data->map.map[i][j] == '0' || data->map.map[i][j] == 'X' || data->map.map[i][j] == 'N')
// 				put_pixel(&data->img, startx + k, starty, color);
// 			if (!data->map.map[i][j + 1])
// 				put_pixel(&data->img, startx + step, starty + k, color);
// 		}
// 		for (int k = 0; k < step; k++)
// 		{
// 			if (data->map.map[i][j] == '1' || data->map.map[i][j] == '0' || data->map.map[i][j] == 'X' || data->map.map[i][j] == 'N')
// 				put_pixel(&data->img, startx, starty + k, color);
// 			if (i + 1 == data->map.height)
// 				put_pixel(&data->img, startx + k, starty + step, color);
// 		}
// 		startx += step;
// 	}
// 	starty += step;
// }
// data->step_max = 50;
// mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
// move_enemies(data, EDrawx, EDrawy);