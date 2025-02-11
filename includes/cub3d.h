/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:39 by clouaint          #+#    #+#             */
/*   Updated: 2025/02/11 19:13:45 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_MAX 400

# ifndef BONUS
#  define BONUS 0
# endif

# define ENEMY1 "assets/ennemies/waechter1.xpm"
# define ENEMY2 "assets/ennemies/waechter2.xpm"
# define ENEMY3 "assets/ennemies/waechter3.xpm"
# define ENEMY4 "assets/ennemies/waechter4.xpm"
# define ENEMY5 "assets/ennemies/waechter5.xpm"
# define ENEMY6 "assets/ennemies/waechter6.xpm"

typedef struct s_node
{
	float	f;
	float	g;
	float	h;
	int		prev_x;
	int		prev_y;
}				t_node;

typedef struct s_sprite
{
	float	sprite_x;
	float	sprite_y;
	float	inv_det;
	float	transform_x;
	float	transform_y;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	float	wall_dist_buffer[WIDTH];
}	t_sprite;

typedef struct s_entity
{
	float		x;
	float		y;
	int			nx;
	int			ny;
	float		distance;
	int			is_alive;
	int			targeted;
	char		**closed_list;
	t_node		**node;
}	t_entity;

typedef struct s_img
{
	int		color;
	void	*img;
	int		*addr;
	int		width;
	int		height;
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
	char	*door;
	char	**map;
	int		height;
	int		width;
	int		player;
}				t_map;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	wall_dist;
	int		line_height;
	int		is_door;
	int		hit;
}				t_raycast;

typedef struct s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}				t_key;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_entity	*entity;
	t_sprite	sprite;
	t_img		tex[5];
	t_img		enemy[6];
	t_img		weapon[2];
	t_img		health[2];
	t_map		map;
	t_img		img;
	t_img		minimap;
	t_raycast	raycast;
	t_key		key;
	float		player_x;
	float		player_y;
	float		angle;
	int			last_x;
	int			nb_entity;
	int			killed;
	int			current_sprite;
	int			shot;
	float		speed;
	int			hp;
	int			hp_max;
	int			p_frame_count;
	int			w_frame_count;
	int			step_max;
	int			draw_start;
	int			draw_end;
}				t_data;

void	fill_map(int fd, t_map *map);
void	init_texture(int fd, t_map *map, t_data *data);
int		get_color(t_data *data, char *str);
void	put_pixel(t_img *image, int x, int y, int color);
int		game_loop(t_data *data);
void	set_img(t_data *data);
void	find_initial_position(t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	check_file_format(char *filename);
void	draw_line(t_data *data, int start, int end, int x);
void	init_raycast(t_raycast *r, t_data *data, int x);
int		check_ray_hit(t_raycast *r, t_data *data);
int		player_move(t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
int		shot(int keycode, int x, int y, t_data *data);
void	finish_game(t_data *data);
void	set_step(t_data *data);
void	init_ray_dir(t_data *data);
void	draw_limits(t_raycast *raycast, int *draw_start, int *draw_end);
void	apply_tex(t_data *data, int x);
void	get_textures(t_data *data, char *path, t_img *tex);
void	draw_bg(t_data *data);
void	find_angle(t_data *data, int i, int j);
void	camera_move(t_data *data);
int		set_tex_i(t_raycast *raycast);
void	render_minimap(t_data *data);
void	init_ennemy(t_data *data);
void	iswap(int *a, int *b);
void	fswap(float *a, float *b);
void	calculate_sprite_projection(t_data *data, t_raycast *raycast, int i);
void	set_draw_range(t_data *data);
void	draw_sprite(t_data *data, int i);
void	load_enemy(t_data *data);
void	animate_player(t_data *data);
void	load_textures(t_data *data);
void	interact(t_data *data);
void	check_errors(t_data *data);
void	init_raycast(t_raycast *r, t_data *data, int x);
void	sort_sprites(t_data *data);
void	enemies(t_data *data);
void	fill_node(t_data *data, t_entity *e, int x, int y);
void	find_min_node(t_data *data, t_entity *entity, int *x, int *y);
void	init_lists(t_data *data, t_entity *entity);
void	free_lists(t_data *data, t_entity *entity);
int		check_list(t_data *data, t_entity *entity);
int		exit_game(t_data *data);
void	init_value(t_data *data);
void	free_map(char **map, int height);
void	check_letter(char *line, int *i, t_map *map);
char	*set_texture(char *line, int *nb_value);
void	init_entity(t_data *data);
void	check_nb_value(t_data *data, int fd, int i, int nb_value);
void	set_node(t_entity *entity, int i, int j);

#endif