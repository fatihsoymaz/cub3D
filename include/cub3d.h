/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:15:23 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 21:08:22 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../include/get_next_line/get_next_line.h"
# include "../include/libft/libft.h"
# include "../include/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600
# define SIZE 64
# define BLOCK_SIZE 64
# define ESC 53
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03
# define FOV 1.0
# define ANGLE_STEP 0.001

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef enum s_side
{
	EAST_WEST,
	NORTH_SOUTH
}					t_side;

typedef struct s_ray
{
	t_point			ray_dir;
	t_point			side_dist;
	t_point			delta_dist;

	int				map_x;
	int				map_y;

	double			perp_wall_dist;

	int				step_x;
	int				step_y;

	int				side;
	int				hit;

	t_img			*img;
	int				tex_x;
}					t_ray;

typedef struct s_map
{
	char			**map;
	char			**map2;
	char			*so;
	char			*no;
	char			*we;
	char			*ea;
	int				*c;
	int				*f;
	double			p_col;
	double			p_row;
	char			type;
	int				count;
	int				map_row;
	int				map_col;
}					t_map;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			dir_radian;
	char			dir;
}					t_player;

typedef struct s_data
{
	t_map			map;
	void			*mlx;
	void			*mlx_win;
	void			*no_img;
	void			*so_img;
	void			*ea_img;
	void			*we_img;
	int				ceiling_color;
	int				floor_color;
	struct s_img	*img_data;
	t_img			imgs[4];
	struct s_player	*player;
	int				key;
	int				mouse_x;
}					t_data;

char				*ft_ret(char *str);
void				ft_err(void);
int					ft_wh_sp(char c);
int					ft_sp_ctrl(char *str);
void				path_check(t_data *fc);
void				control2(t_data *data, char *str);
int					*ft_ret_fc(char *str, char c);
void				ft_nosw(char *str, t_data *game);
void				ft_get_map2(t_data *data);
void				map_free(char **map);
char				*ft_strjoin_v2(char *str, char buffer, int len);
int					map_lines(char *str);
void				del_wspace(char **str);
void				free_func(t_data *data);
void				path_checker(char **str, t_data *data);
char				**duplicate_to_map(t_data *data);
void				ctrl(t_data *data);
void				space_full(char **str);
void				empty_line(char **str, int *k, t_data *data);
void				w_rgb_to_map(t_data *data);
void				wall_image(t_data *data);
void				player_vals(t_data *data);
void				set_dir(t_player *player);
void				init_player(t_data *data);
void				take_img_next(t_data *data);
void				ft_map2(int *i, t_data *game);
void				text_nswe(t_data *game);
void				ft_get_map(char *str, t_data *game);
void				set_dir(t_player *player);
void				player_vals(t_data *data);
void				init_player(t_data *data);
void				ft_move(t_player *player, int dir, t_data *data);
void				ft_turn(t_player *player, char dir);
int					render(t_data *data);
int					close_window(void);
int					ft_press(int key, t_data *data);
int					ft_release(int key, t_data *data);
int					is_collide(double new_x, double new_y, t_data *data);
void				move(t_player *player, double dx, double dy, t_data *data);
void				init_hooks(t_data *data);
void				draw_floor_ceiling(t_data *data, int x, int lineHeight);
int					is_boundary_violated(t_ray *ray, int map_size);
void				determine_texture(t_data *data, t_ray *ray);
int					is_hit(t_ray *ray, t_data *data);
void				calculate_perpetual(t_data *data, t_ray *ray);
unsigned int		get_pixel_color(int tex_y, t_ray *ray);
int					get_tex_y(int y, int line_height);
void				calculate_texture_x(t_data *data, t_ray *ray);
int					safe_divide(int numerator, double denominator);
void				fix_mirror(t_ray *ray);
void				draw_floor_ceiling(t_data *data, int x, int lineHeight);
void				draw_textured_line(t_data *data, t_ray *ray, int x,
						int line_height);
void				ray_step(t_ray *ray);
void				calculate_step_and_dist(t_data *data, t_ray *ray);
void				init_ray(t_data *data, t_ray *ray, double angle);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
#endif