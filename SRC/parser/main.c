/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:34:44 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/06 22:59:35 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_map2(int *i, t_data *game)
{
	int	j;

	j = (*i);
	while (game->map.map[*i])
		(*i)++;
	game->map.map2 = malloc(sizeof(char *) * (*i - j + 1));
	(*i) = j + 1;
	j = 0;
	while (game->map.map[*i])
	{
		game->map.map2[j] = game->map.map[*i];
		(*i)++;
		j++;
	}
	game->map.map2[j] = 0;
	game->map.map_row = j;
}

void	text_nswe(t_data *game)
{
	int	i;

	i = -1;
	while (game->map.map[++i])
	{
		if (ft_sp_ctrl(game->map.map[i]) == 0)
			ft_err();
		ft_nosw(game->map.map[i], game);
		control2(game, game->map.map[i]);
		free(game->map.map[i]);
		if (game->map.no && game->map.so && game->map.we && \
		game->map.ea && game->map.c && game->map.f)
			break ;
	}
	ft_map2(&i, game);
}

void	ft_get_map(char *str, t_data *game)
{
	int	fd;
	int	i;
	int	j;

	i = -1;
	j = map_lines(str);
	fd = open(str, O_RDONLY, 0777);
	game->map.map = malloc(sizeof(char *) * (j + 1));
	while (++i < j)
		game->map.map[i] = get_next_line(fd);
	game->map.map[i] = NULL;
	close(fd);
	text_nswe(game);
}

void	take_img_next(t_data *data)
{
	int	size;

	size = 64;
	data->no_img = mlx_xpm_file_to_image(data->mlx, data->map.no, &size, &size);
	data->so_img = mlx_xpm_file_to_image(data->mlx, data->map.so, &size, &size);
	data->ea_img = mlx_xpm_file_to_image(data->mlx, data->map.ea, &size, &size);
	data->we_img = mlx_xpm_file_to_image(data->mlx, data->map.we, &size, &size);
}

void	player_vals(t_data *data)
{
	data->player->pos_x = data->map.p_col;
	data->player->pos_y = data->map.p_row;
	data->player->dir = data->map.type;
}

void	set_dir(t_player *player)
{
	if (player->dir == 'N')
		player->dir_radian = M_PI * 3 / 2;
	else if (player->dir == 'S')
		player->dir_radian = M_PI / 2;
	else if (player->dir == 'E')
		player->dir_radian = 2 * M_PI;
	else if (player->dir == 'W')
		player->dir_radian = M_PI;
}

void	init_player(t_data *data)
{
	data->player->pos_x += 0.5;
	data->player->pos_y = data->map.p_row + 0.5;
	data->player->dir_y = 0;
	set_dir(data->player);
}

int	close_window(void)
{
	exit(0);
}

int	ft_press(int key, t_data *data)
{
	data->key = key;
	if (key == 53)
		close_window();
	return (0);
}

int	ft_release(int key, t_data *data)
{
	if (key == data->key)
		data->key = -1;
	return (0);
}

int	is_collide(double new_x, double new_y, t_data *data)
{
	if (data->map.map2[(int)(new_y)][(int)(new_x)] == '1' || \
	data->map.map2[(int)(new_y)][(int)(new_x)] == ' ' || \
	data->map.map2[(int)(new_y)][(int)(new_x)] == '\0')
		return (1);
	return (0);
}

void	move(t_player *player, double dx, double dy, t_data *data)
{
	double	old_pos_x;
	double	old_pos_y;

	old_pos_x = player->pos_x;
	old_pos_y = player->pos_y;
	player->pos_x += dx * MOVE_SPEED;
	player->pos_y += dy * MOVE_SPEED;
	if (is_collide(player->pos_x, player->pos_y, data))
	{
		player->pos_x = old_pos_x;
		player->pos_y = old_pos_y;
	}
}

void	ft_move(t_player *player, int dir, t_data *data)
{
	if (dir == 'N')
		move(player, player->dir_x, player->dir_y, data);
	else if (dir == 'S')
		move(player, -player->dir_x, -player->dir_y, data);
	else if (dir == 'E')
		move(player, -player->dir_y, player->dir_x, data);
	else if (dir == 'W')
		move(player, player->dir_y, -player->dir_x, data);
}

void	ft_turn(t_player *player, char dir)
{
	if (dir == LEFT_ARROW)
	{
		player->dir_radian -= ROT_SPEED;
		if (player->dir_radian < 0)
			player->dir_radian += 2 * M_PI;
	}
	if (dir == RIGHT_ARROW)
	{
		player->dir_radian += ROT_SPEED;
		if (player->dir_radian > 2 * M_PI)
			player->dir_radian -= 2 * M_PI;
	}
}

void	init_ray(t_data *data, t_ray *ray, double angle)
{
	ray->ray_dir.x = cos(angle);
	ray->ray_dir.y = sin(angle);
	ray->map_x = (int)data->player->pos_x;
	ray->map_y = (int)data->player->pos_y;
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
}

void	calculate_step(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir.y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

void	calculate_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
		ray->side_dist.x = (data->player->pos_x - ray->map_x) \
		* ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->map_x + 1.0 - data->player->pos_x) \
		* ray->delta_dist.x;
	if (ray->ray_dir.y < 0)
		ray->side_dist.y = (data->player->pos_y - ray->map_y) \
		* ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->map_y + 1.0 - data->player->pos_y) \
		* ray->delta_dist.y;
}

void	calculate_step_and_dist(t_data *data, t_ray *ray)
{
	calculate_step(ray);
	calculate_dist(data, ray);
}

void	ray_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
		ray->side = EAST_WEST;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
		ray->side = NORTH_SOUTH;
	}
}

int	is_boundary_violated(t_ray *ray, int map_size)
{
	if (ray->map_x < 0 || ray->map_y < 0)
		return (1);
	if (ray->map_x >= map_size || ray->map_y >= map_size)
		return (1);
	return (0);
}

void	determine_texture(t_data *data, t_ray *ray)
{
	if (ray->side == EAST_WEST)
	{
		if (ray->ray_dir.x > 0)
			ray->texture = (&data->imgs[3]);
		else
			ray->texture = (&data->imgs[0]);
	}
	else
	{
		if (ray->ray_dir.y > 0)
			ray->texture = (&data->imgs[1]);
		else
			ray->texture = (&data->imgs[2]);
	}
}

int	is_hit(t_ray *ray, t_data *data)
{
	if (is_boundary_violated(ray, WIDTH))
		return (1);
	if (data->map.map2[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	calculate_perpetual(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		ray_step(ray);
		if (is_hit(ray, data))
			ray->hit = 1;
	}
	if (ray->side == EAST_WEST)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	fix_mirror(t_ray *ray)
{
	if ((ray->side == 0 && ray->ray_dir.x < 0) || (ray->side == 1 \
		&& ray->ray_dir.y > 0))
		ray->tex_x = 64 - ray->tex_x - 1;
}

int	safe_divide(int numerator, double denominator)
{
	if (denominator < 1e-5)
		denominator = 0.001;
	return ((int)(numerator / denominator));
}

void	calculate_texture_x(t_data *data, t_ray *ray)
{
	double	wallx;

	if (ray->side == EAST_WEST)
		wallx = data->player->pos_y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wallx = data->player->pos_x + ray->perp_wall_dist * ray->ray_dir.x;
	wallx -= floor((wallx));
	ray->tex_x = (int)(wallx * (double)(64));
	fix_mirror(ray);
}

int	get_tex_y(int y, t_ray *ray, int line_height)
{
	double	tmp;
	double	half_screen_height;
	double	half_line_height;
	double	texture_height;
	int		tex_y;

	(void)ray;
	half_screen_height = WINDOW_HEIGHT / 2.0;
	half_line_height = line_height / 2.0;
	texture_height = (double)(64);
	tmp = (y - half_screen_height + half_line_height);
	tmp *= texture_height / line_height;
	tex_y = (int)tmp;
	return (tex_y);
}

int	get_pixel_color(int tex_y, t_ray *ray)
{
	int	pixel_color;
	int	texture_byte_size;
	int	texture_offset;

	texture_byte_size = ray->texture->bpp / 8;
	texture_offset = (tex_y * ray->texture->line_length);
	texture_offset += ray->tex_x * texture_byte_size;
	pixel_color = *(unsigned int *)(ray->texture->addr + texture_offset);
	return (pixel_color);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	offset = (y * data->line_length + x * (data->bpp / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_textured_line(t_data *data, t_ray *ray, int x, int line_height)
{
	int				line_start;
	int				line_end;
	int				pixel_color;
	int				y;
	int				tex_y;

	line_start = (WINDOW_HEIGHT - line_height) / 2;
	line_end = (WINDOW_HEIGHT + line_height) / 2;
	if (line_start < 0)
		line_start = 0;
	if (line_end > WINDOW_HEIGHT)
		line_end = WINDOW_HEIGHT;
	y = line_start;
	while (++y < line_end)
	{
		tex_y = get_tex_y(y, ray, line_height);
		pixel_color = get_pixel_color(tex_y, ray);
		my_mlx_pixel_put(data->img_data, x, y, pixel_color);
	}
}

void	draw_floor_ceiling(t_data *data, int x, int lineHeight)
{
	int	start;
	int	end;
	int	y;

	start = (WINDOW_HEIGHT - lineHeight) / 2;
	end = (WINDOW_HEIGHT + lineHeight) / 2;
	if (start < 0)
		start = 0;
	if (end > WINDOW_HEIGHT)
		end = WINDOW_HEIGHT;
	y = -1;
	while (++y < start)
		my_mlx_pixel_put(data->img_data, x, y, data->ceiling_color);
	y = end - 1;
	while (++y < WINDOW_HEIGHT)
		my_mlx_pixel_put(data->img_data, x, y, data->floor_color);
}

void	raycast(t_data *data)
{
	double	angle;
	int		line_height;
	t_ray	ray;
	int		x;

	angle = data->player->dir_radian - FOV / 2;
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		init_ray(data, &ray, angle);
		calculate_step_and_dist(data, &ray);
		calculate_perpetual(data, &ray);
		determine_texture(data, &ray);
		calculate_texture_x(data, &ray);
		ray.perp_wall_dist *= cos(data->player->dir_radian - angle);
		line_height = safe_divide(WINDOW_HEIGHT, ray.perp_wall_dist);
		draw_textured_line(data, &ray, x, line_height);
		draw_floor_ceiling(data, x, line_height);
		angle += ANGLE_STEP;
	}
}

void	routine(t_data *data)
{
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->img_data->img, 0, 0);
}

int	render(t_data *data)
{
	data->player->dir_x = cos(data->player->dir_radian);
	data->player->dir_y = sin(data->player->dir_radian);
	if (data->key == W)
		ft_move(data->player, 'N', data);
	else if (data->key == S)
		ft_move(data->player, 'S', data);
	else if (data->key == A)
		ft_move(data->player, 'W', data);
	else if (data->key == D)
		ft_move(data->player, 'E', data);
	else if (data->key == LEFT_ARROW)
		ft_turn((data->player), LEFT_ARROW);
	else if (data->key == RIGHT_ARROW)
		ft_turn((data->player), RIGHT_ARROW);
	routine(data);
	return (0);
}

int	cub_mouse(int x, int y, t_data *data)
{
	(void)y;
	data->player->dir_radian += (x - data->mouse_x) / 100.0;
	data->mouse_x = x;
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 06, 1L << 6, cub_mouse, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, NULL);
	mlx_hook(data->mlx_win, 2, 0, ft_press, data);
	mlx_hook(data->mlx_win, 3, 0, ft_release, data);
	mlx_loop_hook(data->mlx, render, data);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	take_img_next(data);
	w_rgb_to_map(data);
	wall_image(data);
	player_vals(data);
	data->key = -1;
	init_player(data);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	init_hooks(data);
	mlx_loop(data->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = ft_calloc(sizeof(t_data), 1);
		ft_get_map(av[1], data);
		path_check(data);
		ft_get_map2(data);
		data->img_data = ft_calloc(sizeof(t_img), 1);
		data->player = ft_calloc(sizeof(t_player), 1);
		if (!init_mlx(data))
			ft_err();
		free_func(data);
	}
	else
		ft_err();
}
