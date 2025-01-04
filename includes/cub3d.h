/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:39 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/04 19:25:46 by nferrad          ###   ########.fr       */
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
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	*path;
	char	*floor;
	char	*cell;
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	**map;
	int		height;
	int		width;
}				t_map;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	plane_x;
	double	plane_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
	int		line_height;
}				t_raycast;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_img		img;
	t_raycast	raycast;
	void		*wall;
	int			zoom;
	int			startx;
	int			starty;
	int			player_x;
	int			player_y;
	int			last_x;
	float		angle;
	int			color;
}				t_data;

void	draw_square(t_data *data);
void	print_texture(t_map *map);
void	fill_map(int fd, t_map *map);
void	init_texture(int fd, t_map *map);
int		get_color(t_data *data, char *str);
int		render_floor(t_data *data, int size);
void	put_pixel(t_img *image, int x, int y, int color);
int		game_loop(t_data *data);
void	set_img(t_data *data);
void	find_initial_position(t_data *data);
void	is_cub(const char *str);
int		mouse_move(int x, int y, t_data *data);
void	check_file_format(char *filename);
void	draw_line(t_data *data, int start, int end, int x);
void	init_raycast(t_data *data, double dirX, double dirY, int x);
int		check_ray_hit(t_data *data);
void	set_step(t_data *data);

#endif