#ifndef CUB3D_H
#define CUB3D_H

#include "../include/get_next_line/get_next_line.h"
#include "../include/libft/libft.h"
#include "../include/mlx/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
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
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define FOV 1.047198
# define ANGLE_STEP 0.001309
# define OFFSET 0.6
# define COLLIDE_MULTIPLIER 1.5

typedef struct s_img
{
	void *img;
	char *addr;
	int bpp;
	int line_length;
	int endian;
} t_img;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef enum s_side
{
	EAST_WEST,
	NORTH_SOUTH
}	t_side;



typedef struct s_ray
{
	t_point		ray_dir;
	t_point		side_dist;
	t_point		delta_dist;

	int			map_x;
	int			map_y;

	double		perp_wall_dist;

	int			step_x;
	int			step_y;

	int			side;
	int			hit;

	t_img		*texture;
	int			tex_x;
}			t_ray;

typedef struct s_map
{
	char **map;
	char **map2;
	char *so;
	char *no;
	char *we;
	char *ea;
	int *c;
	int *f;
	int i; // silinecek değerleri görmek için yazıldı
	double p_col;
	double p_row;
	char type;
	int count; // NSEW sayisini takip etmek için kullanıyorum
	int map_row;
	int map_col;
} t_map;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double dir_radian;
	char dir;
} t_player;

typedef struct s_data
{
	t_map map;
	void *mlx;
	void *mlx_win;
	void *no_img;
	void *so_img;
	void *ea_img;
	void *we_img;
	char rgb_flag;
	int ceiling_color;
	int floor_color;
	struct s_img *img_data;
	t_img imgs[4];
	struct s_player *player;
	int key;
	int mouse_x;

} t_data;

char *ft_ret(char *str);
void ft_err(void);
int ft_wh_sp(char c);
int count_wd(char *s);
int count_comma(char *s);
int ft_sp_ctrl(char *str);
void path_check(t_data *fc);
void control2(t_data *data, char *str);
int *ft_ret_fc(char *str, char c);
void ft_nosw(char *str, t_data *game);
void ft_get_map2(t_data *data);
void map_free(char **map);
char *ft_strjoin_v2(char *str, char buffer, int len);
int map_lines(char *str);
void del_wspace(char **str);
void free_func(t_data *data);
void path_checker(char **str, t_data *data);
char **duplicate_to_map(t_data *data);
void ctrl(t_data *data);
void space_full(char **str);
void empty_line(char **str, int *k, t_data *data);
void w_rgb_to_map(t_data *data);
void wall_image(t_data *data);
void player_vals(t_data *data);
void set_dir(t_player *player);
void init_player(t_data *data);
void take_img_next(t_data *data);
#endif