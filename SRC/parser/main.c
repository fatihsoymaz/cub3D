/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:34:44 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 21:10:56 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	take_img_next(t_data *data)
{
	int	size;

	size = 64;
	data->no_img = mlx_xpm_file_to_image(data->mlx, data->map.no, &size, &size);
	data->so_img = mlx_xpm_file_to_image(data->mlx, data->map.so, &size, &size);
	data->ea_img = mlx_xpm_file_to_image(data->mlx, data->map.ea, &size, &size);
	data->we_img = mlx_xpm_file_to_image(data->mlx, data->map.we, &size, &size);
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

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * data->line_length + x * (data->bpp / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
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
