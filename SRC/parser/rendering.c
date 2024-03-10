/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:56:02 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 23:07:06 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	raycast(t_data *data)
{
	double	angle;
	int		line_height;
	t_ray	ray;
	int		x;

	angle = data->player->dir_radian - FOV / 2;
	x = -1;
	while (++x < WIDTH)
	{
		init_ray(data, &ray, angle);
		calculate_step_and_dist(data, &ray);
		calculate_perpetual(data, &ray);
		determine_texture(data, &ray);
		calculate_texture_x(data, &ray);
		ray.perp_wall_dist *= cos(data->player->dir_radian - angle);
		line_height = safe_divide(HEIGHT, ray.perp_wall_dist);
		draw_textured_line(data, &ray, x, line_height);
		draw_floor_ceiling(data, x, line_height);
		angle += ANGLE_STEP;
	}
}

void	routine(t_data *data)
{
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data->img, 0,
		0);
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
