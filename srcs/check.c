/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:50:14 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/04 19:25:18 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_format(char *filename)
{
	int		i;

	i = 0;
	if (!filename)
	{
		ft_printf("Error : No file\n");
		exit(-1);
	}
	while (filename[i] && filename[i - 1] != '.')
		i++;
	if (!ft_strncmp((filename + i), "cub", 3))
		return ;
	ft_printf("Error : File not .cub\n");
	exit(-1);
}

int	check_map_lines(t_map *map, int i, int j)
{
	if (!map->map || !map->map[i] || i < 0 || i>= map->height|| j < 0 || j >=(int)ft_strlen(map->map[i]))
	{
		ft_printf("Error map\n");
		return (0);
	}
	while (map->map[i][j] == ' ') // ajouter les autres white spaces ?
		j++;
	while (map->map[i][j])
	{
		if (map->map[i][j] != '1')
		{
			ft_printf("Map is not properly closed at the top or the bottom\n");
			return (0);
		}
		j++;
	}
	return (1);
}

// int	is_corner(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (i < map->height)
// 	{
// 		j = 1;
// 		while (map->map[i][j] == ' ' || map->map[i][j] == '1')
// 			j++;
// 		if (map->map[i - 1][j] != '1' && map->map[i][j - 1] != '1')
// 		{
// 			printf("Corner is open\n");
// 			return (0);
// 		}
// 		printf("%c\n", map->map[i - 1][j]);
// 		i++;
// 	}
// 	return (1);
// }

void is_map_closed(t_data *data)
{
	int	i;
	int	j;

	if (!check_map_lines(&data->map, 0, 0))
		finish_game(data);
	i = 1;
	while (i < data->map.height - 1)
	{
		j = ft_strlen(data->map.map[i]) - 1;
		if (data->map.map[i][j] != '1')
			{
				ft_printf("Map is not properly closed on sides\n");
				finish_game(data);
			}
		i++;
	}
	if (!check_map_lines(&data->map, i, 0))
		finish_game(data);
	// if (!is_corner(&data->map))
	// 	finish_game(data);
}


void	check_errors(t_data *data)
{
	check_file_format(data->map.path);
	// is_map_closed(data);
}
