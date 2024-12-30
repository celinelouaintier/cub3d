/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:39 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/30 16:24:07 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

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
	int     height;
	int     width;
}               t_map;

typedef struct  s_data
{
    void    *mlx;
    void    *window;
	t_map	map;
    t_img   img;
    void    *wall;
    int     zoom;
	int		startx;
	int		starty;
}               t_data;

void	draw_square(t_data *data);
void    print_texture(t_map *map);
void	fill_map(int fd, t_map *map);
void    init_texture(int fd, t_map *map);
int     get_color(t_data *data, char *str);
int     render_floor(t_data *data, int size);
void	put_pixel(t_img *image, int x, int y, int color);
int		game_loop(t_data *data);
void	set_img(t_data *data);

#endif