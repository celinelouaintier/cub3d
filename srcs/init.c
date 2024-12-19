/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:48:36 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/19 21:50:33 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_texture(t_map *map)
{
	ft_printf("NO : %s", map->no);
	ft_printf("SO : %s", map->so);
	ft_printf("WE : %s", map->we);
	ft_printf("EA : %s", map->ea);
	ft_printf("F : %s", map->floor);
	ft_printf("C : %s", map->cell);
}

char	*set_texture(char *line)
{
	char	c;

	line += 2;
	c = *line;
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		line++;
	while (*line == ' ')
		line++;
	return (line);
}

void	init_texture(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!line)
			break ;
		if (*line == 'N')
			map->no = set_texture(line);
		else if (*line == 'S')
			map->so = set_texture(line);
		else if (*line == 'W')
			map->we = set_texture(line);
		else if (*line == 'E')
			map->ea = set_texture(line);
		else if (*line == 'F')
			map->floor = set_texture(line);
		else if (*line == 'C')
			map->cell = set_texture(line);
		line = get_next_line(fd);
	}
}
