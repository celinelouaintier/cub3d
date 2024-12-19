/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:48:36 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/19 19:04:20 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_texture(t_map *map)
{
    ft_printf("NO : %s", map->no);
    ft_printf("SO : %s", map->so);
    ft_printf("WE : %s", map->we);
    ft_printf("EA : %s", map->ea);
    ft_printf("F : %s", map->floor);
    ft_printf("C : %s", map->cell);
}

void init_texture(int fd, t_map *map)
{
    int     nb_value;
    char    *line;

    nb_value = 0;
    while (nb_value < 6)
    {
        line = get_next_line(fd);
        if(!line)
            break ;
        if (!ft_strncmp(line, "NO", 2))
        {
            line += 2;
            while (*line == ' ')
                line++;
            map->no = ft_strdup(line);
            nb_value++;
        }
        else if (!ft_strncmp(line, "SO", 2))
        {
            line += 2;
            while (*line == ' ')
                line++;
            map->so = ft_strdup(line);
            nb_value++;
        }
        else if (!ft_strncmp(line, "WE", 2))
        {
            line += 2;
            while (*line == ' ')
                line++;
            map->we = ft_strdup(line);
            nb_value++;
        }
        else if (!ft_strncmp(line, "EA", 2))
        {
            line += 2;
            while (*line == ' ')
                line++;
            map->ea = ft_strdup(line);
            nb_value++;
        }
        else if (!ft_strncmp(line, "F", 1))
        {
            line += 1;
            while (*line == ' ')
                line++;
            map->floor = ft_strdup(line);
            nb_value++;
        }
        else if (!ft_strncmp(line, "C", 1))
        {
            line += 1;
            while (*line == ' ')
                line++;
            map->cell = ft_strdup(line);
            nb_value++;
        }
    }
    print_texture(map);
}
