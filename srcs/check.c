/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:50:14 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/12 15:24:36 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_format(char *filename, int fd, t_data *data)
{
	int		i;

	i = 0;
	if (!filename || fd < 0)
	{
		ft_printf("Error\nNo file\n");
		free(data);
		exit(-1);
	}
	while (filename[i] && filename[i - 1] != '.')
		i++;
	if (!ft_strncmp((filename + i), "cub", 3))
		return ;
	ft_printf("Error\nFile not .cub\n");
	exit(-1);
}

int	is_map_closed(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] != '1' && map->map[y][x] != ' ')
			{
				if (y == 0 || y == map->height - 1)
					return (ft_printf("Error\nMap is not closed\n") - 24);
				if (!map->map[y][x + 1] || map->map[y][x + 1] == ' ')
					return (ft_printf("Error\nMap is not closed\n") - 24);
				else if (!map->map[y][x - 1] || map->map[y][x - 1] == ' ')
					return (ft_printf("Error\nMap is not closed\n") - 24);
				else if (!map->map[y + 1][x] || map->map[y + 1][x] == ' ')
					return (ft_printf("Error\nMap is not closed\n") - 24);
				else if (!map->map[y - 1][x] || map->map[y - 1][x] == ' ')
					return (ft_printf("Error\nMap is not closed\n") - 24);
			}
		}
	}
	return (1);
}

int	check_map_char(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height - 1)
	{
		j = -1;
		while (++j < (int)ft_strlen(map->map[i]) - 1)
		{
			if (map->map[i][j] != '0' && map->map[i][j] != ' '
				&& map->map[i][j] != '1' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'W'
				&& (!BONUS || (map->map[i][j] != 'D' && map->map[i][j] != 'X')))
			{
				ft_printf("Error\nWrong character in your map : %c\n",
					map->map[i][j]);
				return (0);
			}
			else if (map->map[i][j] == 'N' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'S')
				map->player++;
		}
	}
	return (1);
}

void	check_errors(t_data *data)
{
	data->map.player = 0;
	if (!is_map_closed(&data->map) || !check_map_char(&data->map))
		exit_game(data);
	if (data->map.player != 1)
	{
		ft_printf("Error\nWarning, %d player(s) in your map\n",
			data->map.player);
		exit_game(data);
	}
}

void	check_letter(char *line, int *i, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
		map->no = set_texture(line, i);
	else if (line[0] == 'S' && line[1] == 'O')
		map->so = set_texture(line, i);
	else if (line[0] == 'W' && line[1] == 'E')
		map->we = set_texture(line, i);
	else if (line[0] == 'E' && line[1] == 'A')
		map->ea = set_texture(line, i);
	else if (line[0] == 'F' && line[1] == ' ')
		map->floor = set_texture(line, i);
	else if (line[0] == 'C' && line[1] == ' ')
		map->cell = set_texture(line, i);
	else if (BONUS && line[0] == 'D' && line[1] == ' ')
		map->door = set_texture(line, i);
}
