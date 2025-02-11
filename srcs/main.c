/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:48 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/11 19:13:26 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_node(t_entity *entity, int i, int j)
{
	entity->node[i][j].f = 99999;
	entity->node[i][j].g = 99999;
	entity->node[i][j].h = 99999;
	entity->node[i][j].prev_x = -1;
	entity->node[i][j].prev_y = -1;
}

void	animate_player(t_data *data)
{
	data->p_frame_count++;
	if (data->p_frame_count >= 7)
	{
		data->current_sprite = (data->current_sprite + 1) % 6;
		data->p_frame_count = 0;
	}
}

void	hook(t_data *data)
{
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
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	check_file_format(av[1]);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	if (ac != 2)
		return (1);
	data->map.path = av[1];
	fd = open(data->map.path, O_RDONLY);
	init_value(data);
	init_texture(fd, &data->map, data);
	check_errors(data);
	find_initial_position(data);
	if (BONUS)
		init_ennemy(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	load_textures(data);
	hook(data);
	finish_game(data);
	return (0);
}

// mlx_mouse_hide(data->mlx, data->window);