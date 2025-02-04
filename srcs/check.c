/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:50:14 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/04 22:52:10 by clouaint         ###   ########.fr       */
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

int is_map_closed(t_map *map)
{
	int	i;
	int	j;
    
	i = -1;
    while (++i < map->height)
    {
        j = 0;
        while (map->map[i][j] == ' ')
            j++;
        if (map->map[i][j] != '1')
        {
            ft_printf("Line %d does not start with '1'\n", i);
            return (0);
        }
        j = ft_strlen(map->map[i]) - 1;
        while (j >= 0 && map->map[i][j] == ' ')
            j--;
        if (j >= 0 && map->map[i][j] != '1')
        {
            ft_printf("Line %d does not end with '1'\n", i);
            return (0);
        }
    }
	j = -1;
    while (++j < map->width)
    {
        i = 0;
        while (i < map->height && (j >= (int)ft_strlen(map->map[i]) || map->map[i][j] == ' '))
            i++;
        if (i < map->height && map->map[i][j] != '1')
        {
            ft_printf("Column %d does not start with '1'\n", j);
            return (0);
        }
        i = map->height - 1;
        while (i >= 0 && (j >= (int)ft_strlen(map->map[i]) || map->map[i][j] == ' '))
            i--;
        if (i >= 0 && map->map[i][j] != '1')
        {
            ft_printf("Column %d does not end with '1'\n", j);
            return (0);
        }
    }
    return (1);
}

void	check_errors(t_data *data)
{
	check_file_format(data->map.path);
	if (!is_map_closed(&data->map))
	{
		ft_printf("Error : Map is not closed\n");
		finish_game(data);
	}
}
