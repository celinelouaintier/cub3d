/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:46:17 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/28 13:16:09 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_data *data, char *path)
{
	static int	i;
	t_img		*tex;

	tex = &data->tex[i];
	if (path == NULL)
	{
		perror("Texture path is NULL");
		finish_game(data);
	}
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("failed to load texture at index %d\n", i);
		finish_game(data);
	}
	if (tex->width <= 0 || tex->height <= 0)
	{
		perror("Invalid texture dimension\n");
		finish_game(data);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->pixel_bits, &tex->size_line, &tex->endian);
	if (!tex->addr)
	{
		perror("Failed to get image address\n");
		finish_game(data);
	}
	i++;
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
