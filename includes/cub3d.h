/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:39 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/21 23:16:02 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

typedef struct  s_map
{
	char	*path;
    char    *floor;
    char    *cell;
    char    *so;
    char    *no;
    char    *we;
    char    *ea;
	char	**map;
	int	height;
	int	width;
}               t_map;

typedef struct  s_data
{
    void    *mlx;
    void    *window;
	t_map	map;
}               t_data;

void init_texture(int fd, t_map *map);

void    print_texture(t_map *map);

#endif