/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:48:36 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/23 18:13:32 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_texture(t_map *map)
{
	ft_printf("NO : %s", map->no);
	ft_printf("SO : %s", map->so);
	ft_printf("WE : %s", map->we);
	ft_printf("EA : %s", map->ea);
	ft_printf("\n\n");
	ft_printf("F  : %s", map->floor);
	ft_printf("C  : %s", map->cell);
	ft_printf("\n\n");
	ft_printf("Height : %d\n", map->height);
	ft_printf("Width : %d\n", map->width);
	ft_printf("\n\n");

	int i = 0;
	while (map->map[i])
	{
		ft_printf("%s\n", map->map[i]);
		i++;
	}
}

char	*skip_line(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			break ;
		line = get_next_line(fd);
	}
	return (line);
}

char	*set_texture(char *line, int *nb_value)
{
	char	c;

	line += 2;
	c = *line;
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		line++;
	while (*line == ' ')
		line++;
	*nb_value += 1;
	line[ft_strlen(line) - 1] = 0;
	return (line);
}

void	get_map_size(int fd, t_map **map, char *line)
{
	(*map)->width = 0;
	(*map)->height = 0;
	while (line)
	{
		if ((size_t)(*map)->width < ft_strlen(line))
		{
			(*map)->width = ft_strlen(line);
			if (line[ft_strlen(line) - 1] == '\n')
				(*map)->width--;
		}
		while (*line == ' ')
			line++;
		if (*line == '1')
			(*map)->height++;
		line = get_next_line(fd);
	}
	close(fd);
}

void	fill_map(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = -1;
	line = get_next_line(fd);
	line = skip_line(fd);
	get_map_size(fd, &map, line);
	open(map->path, O_RDONLY);
	line = skip_line(fd);
	i = -1;
	map->map = malloc(sizeof(char *) * map->height);
	while (++i < map->height)
	{
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		map->map[i] = ft_strdup(line);
		line = get_next_line(fd);
	}
}

void	init_texture(int fd, t_map *map)
{
	char	*line;
	int		nb_value;

	nb_value = 0;
	while (nb_value < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (*line == ' ')
			line++;
		if (*line == 'N')
			map->no = set_texture(line, &nb_value);
		else if (*line == 'S')
			map->so = set_texture(line, &nb_value);
		else if (*line == 'W')
			map->we = set_texture(line, &nb_value);
		else if (*line == 'E')
			map->ea = set_texture(line, &nb_value);
		else if (*line == 'F')
			map->floor = set_texture(line, &nb_value);
		else if (*line == 'C')
			map->cell = set_texture(line, &nb_value);
	}
}

// map->map[i] = malloc(sizeof(char) * map->width);
// while (line[j] && line[j] != '\n')
// {
// 	map->map[i][j] = line[j];
// 	j++;
// }
// while (j < map->width)
// {
// 	map->map[i][j] = ' ';
// 	j++;
// }