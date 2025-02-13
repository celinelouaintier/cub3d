/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:48:36 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/13 23:16:51 by nferrad          ###   ########.fr       */
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

char	*skip_line(int fd, t_data *data, int check)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			return (line);
		if (check)
			check_letter(line, i, data, fd);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

void	get_map_size(int fd, t_map **map, char *line, t_data *data)
{
	int		empty_line;
	int		i;

	(*map)->width = 0;
	(*map)->height = 0;
	empty_line = 0;
	while (line)
	{
		i = 0;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		if ((size_t)(*map)->width < ft_strlen(line))
			(*map)->width = ft_strlen(line);
		while (line[i] == ' ')
			i++;
		if (line[i] && !empty_line)
			(*map)->height++;
		else if (!line[i])
			empty_line = 1;
		else
			clean_gnl(line, fd, data, "Error\nEmpty line in the map\n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	fill_map(int fd, t_map *map, t_data *data)
{
	int		i;
	char	*line;

	i = -1;
	line = skip_line(fd, data, 1);
	get_map_size(fd, &map, line, data);
	close(fd);
	fd = open(map->path, O_RDONLY);
	line = skip_line(fd, data, 0);
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
	clean_gnl(line, fd, data, NULL);
}

void	set_texture(char *line, char **tex, int fd, t_data *data)
{
	if (*tex)
		clean_gnl(line, fd, data, "Error\nTexture already set\n");
	line += 2;
	while (*line == ' ')
		line++;
	line[ft_strlen(line) - 1] = 0;
	*tex = ft_strdup(line);
}

void	init_texture(int fd, t_map *map, t_data *data)
{
	char	*line;
	char	*memory;
	int		i;

	while (!map->we || !map->ea || !map->so || !map->no || !map->floor
		|| !map->cell)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		memory = line;
		while (line[i] == ' ')
			i++;
		check_letter(line, i, data, fd);
		free(memory);
	}
	fill_map(fd, map, data);
}
