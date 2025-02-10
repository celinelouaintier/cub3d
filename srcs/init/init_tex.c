/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:46:17 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/10 19:46:34 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_value(t_data *data)
{
	data->key.a = 0;
	data->key.w = 0;
	data->key.s = 0;
	data->key.d = 0;
	data->key.left = 0;
	data->key.right = 0;
	data->img.img = NULL;
	data->minimap.img = NULL;
	data->p_frame_count = 0;
	data->w_frame_count = 0;
	data->last_x = -1;
	data->speed = 0.1;
	data->hp_max = 100;
	data->hp = data->hp_max;
}

void	get_textures(t_data *data, char *path, t_img *tex)
{
	if (path == NULL)
	{
		perror("Texture path is NULL");
		finish_game(data);
	}
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		perror("failed to load texture\n");
		finish_game(data);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->pixel_bits,
			&tex->size_line, &tex->endian);
	if (!tex->addr)
	{
		perror("Failed to get image address\n");
		finish_game(data);
	}
}

void	load_textures(t_data *data)
{
	get_textures(data, data->map.no, &data->tex[0]);
	get_textures(data, data->map.so, &data->tex[1]);
	get_textures(data, data->map.we, &data->tex[2]);
	get_textures(data, data->map.ea, &data->tex[3]);
	if (BONUS)
	{
		data->shot = 0;
		data->current_sprite = 0;
		get_textures(data, data->map.door, &data->tex[4]);
		get_textures(data, "assets/weapon/DEAG1.xpm", &data->weapon[0]);
		get_textures(data, "assets/weapon/DEAG2.xpm", &data->weapon[1]);
		get_textures(data, "assets/healthBar/hp_bar_outer.xpm",
			&data->health[0]);
		get_textures(data, "assets/healthBar/hp_bar_inner.xpm",
			&data->health[1]);
		get_textures(data, ENEMY1, &data->enemy[0]);
		get_textures(data, ENEMY2, &data->enemy[1]);
		get_textures(data, ENEMY3, &data->enemy[2]);
		get_textures(data, ENEMY4, &data->enemy[3]);
		get_textures(data, ENEMY5, &data->enemy[4]);
		get_textures(data, ENEMY6, &data->enemy[5]);
	}
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
