/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:46:17 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/13 18:10:59 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tex_struct(t_data *data)
{
	ft_memset(data->tex, 0, sizeof(data->tex));
	if (BONUS)
	{
		memset(data->enemy, 0, sizeof(data->enemy));
		memset(data->weapon, 0, sizeof(data->weapon));
		memset(data->health, 0, sizeof(data->health));
	}
}

void	init_value(t_data *data)
{
	init_tex_struct(data);
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
	data->speed = 0.05;
	data->killed = 0;
	data->hp_max = 100;
	data->hp = data->hp_max;
	data->map.ea = NULL;
	data->map.no = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
	data->map.door = NULL;
	data->map.cell = NULL;
	data->map.floor = NULL;
	data->map.map = NULL;
}

void	get_textures(t_data *data, char *path, t_img *tex)
{
	if (path == NULL)
	{
		ft_printf("Error\nTexture path is NULL\n");
		finish_game(data);
	}
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		ft_printf("Error\nFailed to load texture\n");
		finish_game(data);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->pixel_bits,
			&tex->size_line, &tex->endian);
	if (!tex->addr)
	{
		ft_printf("Error\nFailed to get image address\n");
		finish_game(data);
	}
}

void	load_textures(t_data *data)
{
	get_textures(data, data->map.no, &data->tex[0]);
	get_textures(data, data->map.so, &data->tex[1]);
	get_textures(data, data->map.ea, &data->tex[2]);
	get_textures(data, data->map.we, &data->tex[3]);
	if (BONUS)
	{
		data->shot = 0;
		data->current_sprite = 0;
		if (have_door(data))
			get_textures(data, data->map.door, &data->tex[4]);
		get_textures(data, WEAPON1, &data->weapon[0]);
		get_textures(data, WEAPON2, &data->weapon[1]);
		get_textures(data, WEAPON3, &data->weapon[2]);
		get_textures(data, WEAPON4, &data->weapon[3]);
		get_textures(data, WEAPON5, &data->weapon[4]);
		get_textures(data, HEALTH1, &data->health[0]);
		get_textures(data, HEALTH2, &data->health[1]);
		get_textures(data, ENEMY1, &data->enemy[0]);
		get_textures(data, ENEMY2, &data->enemy[1]);
		get_textures(data, ENEMY3, &data->enemy[2]);
		get_textures(data, ENEMY4, &data->enemy[3]);
		get_textures(data, ENEMY5, &data->enemy[4]);
		get_textures(data, ENEMY6, &data->enemy[5]);
	}
	check_textures_size(data);
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
