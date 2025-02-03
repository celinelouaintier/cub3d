/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:46:17 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/03 21:29:51 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_textures(t_data *data, char *path)
{
	static int	i;
	t_img		*tex;

	tex = &data->tex[i];
	if (path == NULL)
	{
		perror("Texture path is NULL");
		finish_game(data);
	}
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		printf("failed to load texture at index %d\n", i);
		finish_game(data);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->pixel_bits,
			&tex->size_line, &tex->endian);
	if (!tex->addr)
	{
		perror("Failed to get image address\n");
		finish_game(data);
	}
	i++;
}

void	load_textures(t_data *data)
{
	get_textures(data, data->map.no);
	get_textures(data, data->map.so);
	get_textures(data, data->map.we);
	get_textures(data, data->map.ea);
	if (BONUS)
	{
		get_textures(data, data->map.door);
		load_enemy(data);
	}
}

void	load_enemy(t_data *data)
{
	data->current_sprite = 0;
	data->enemy[0].img = mlx_xpm_file_to_image(data->mlx, ENEMY1,
			&data->enemy[0].width, &data->enemy[0].height);
	data->enemy[1].img = mlx_xpm_file_to_image(data->mlx, ENEMY2,
			&data->enemy[1].width, &data->enemy[1].height);
	data->enemy[2].img = mlx_xpm_file_to_image(data->mlx, ENEMY3,
			&data->enemy[2].width, &data->enemy[2].height);
	data->enemy[3].img = mlx_xpm_file_to_image(data->mlx, ENEMY4,
			&data->enemy[3].width, &data->enemy[3].height);
	data->enemy[4].img = mlx_xpm_file_to_image(data->mlx, ENEMY5,
			&data->enemy[4].width, &data->enemy[4].height);
	data->enemy[5].img = mlx_xpm_file_to_image(data->mlx, ENEMY6,
			&data->enemy[5].width, &data->enemy[5].height);
	data->enemy[0].addr = (int *)mlx_get_data_addr(data->enemy[0].img,
			&data->enemy[0].pixel_bits, &data->enemy[0].size_line, &data->enemy[0].endian);
	data->enemy[1].addr = (int *)mlx_get_data_addr(data->enemy[1].img,
			&data->enemy[1].pixel_bits, &data->enemy[1].size_line, &data->enemy[1].endian);
	data->enemy[2].addr = (int *)mlx_get_data_addr(data->enemy[2].img,
			&data->enemy[2].pixel_bits, &data->enemy[2].size_line, &data->enemy[2].endian);
	data->enemy[3].addr = (int *)mlx_get_data_addr(data->enemy[3].img,
			&data->enemy[3].pixel_bits, &data->enemy[3].size_line, &data->enemy[3].endian);
	data->enemy[4].addr = (int *)mlx_get_data_addr(data->enemy[4].img,
			&data->enemy[4].pixel_bits, &data->enemy[4].size_line, &data->enemy[4].endian);
	data->enemy[5].addr = (int *)mlx_get_data_addr(data->enemy[5].img,
			&data->enemy[5].pixel_bits, &data->enemy[5].size_line, &data->enemy[5].endian);
}

int	set_tex_i(t_raycast *raycast)
{
	if (raycast->is_door)
		return (4);
	if (raycast->side && raycast->step_y == -1)
		return (0);
	else if (raycast->side && raycast->step_y == 1)
		return (1);
	else if (!raycast->side && raycast->step_x == 1)
		return (2);
	else if (!raycast->side && raycast->step_x == -1)
		return (3);
	return (-1);
}
