/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:48:36 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/11 20:15:32 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_texture(t_map *map)
// {
// 	ft_printf("NO : %s\n", map->no);
// 	ft_printf("SO : %s\n", map->so);
// 	ft_printf("WE : %s\n", map->we);
// 	ft_printf("EA : %s\n", map->ea);
// 	ft_printf("D : %s\n", map->door);
// 	ft_printf("\n\n");
// 	ft_printf("F  : %s\n", map->floor);
// 	ft_printf("C  : %s", map->cell);
// 	ft_printf("\n\n");
// 	ft_printf("Height : %d\n", map->height);
// 	ft_printf("Width : %d\n", map->width);
// 	ft_printf("\n\n");
// 	// int i = 0;
// 	// while (map->map[i])
// 	// {
// 	// 	ft_printf("%s\n", map->map[i]);
// 	// 	i++;
// 	// }
// }

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
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

void	get_map_size(int fd, t_map **map, char *line)
{
	char	*memory;

	(*map)->width = 0;
	(*map)->height = 0;
	while (line)
	{
		memory = line;
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
		free(memory);
		line = get_next_line(fd);
	}
	close(fd);
}

void	fill_map(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = -1;
	line = skip_line(fd);
	get_map_size(fd, &map, line);
	close(fd);
	fd = open(map->path, O_RDONLY);
	line = skip_line(fd);
	i = -1;
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		free_map(map->map, map->height);
	while (++i < map->height)
	{
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		map->map[i] = line;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

char	*set_texture(char *line, int *nb_value)
{
	line += 2;
	while (*line == ' ')
		line++;
	*nb_value += 1;
	line[ft_strlen(line) - 1] = 0;
	return (ft_strdup(line));
}

void	init_texture(int fd, t_map *map, t_data *data)
{
	char	*line;
	int		nb_value;
	char	*memory;
	int		i;

	nb_value = 6;
	if (BONUS)
		nb_value += 1;
	i = 0;
	while (i < nb_value)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		memory = line;
		while (*line == ' ')
			line++;
		check_letter(line, &i, map);
		free(memory);
	}
	check_nb_value(data, fd, i, nb_value);
	fill_map(fd, map);
}
