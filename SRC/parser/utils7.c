/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:15:50 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 20:31:18 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calculate_line_bounds(int *start, int *end, int line_height)
{
	*start = (HEIGHT - line_height) / 2;
	*end = (HEIGHT + line_height) / 2;
	if (*start < 0)
		*start = 0;
	if (*end > HEIGHT)
		*end = HEIGHT;
}

void	draw_floor_ceiling(t_data *data, int x, int lineHeight)
{
	int	start;
	int	end;
	int	y;

	calculate_line_bounds(&start, &end, lineHeight);
	y = -1;
	while (++y < start)
		my_mlx_pixel_put(data->img_data, x, y, data->ceiling_color);
	y = end - 1;
	while (++y < HEIGHT)
		my_mlx_pixel_put(data->img_data, x, y, data->floor_color);
}

void	draw_textured_line(t_data *data, t_ray *ray, int x, int line_height)
{
	int				line_start;
	int				line_end;
	unsigned int	pixel_color;
	int				y;
	int				tex_y;

	calculate_line_bounds(&line_start, &line_end, line_height);
	y = line_start;
	while (++y < line_end)
	{
		tex_y = get_tex_y(y, line_height);
		pixel_color = get_pixel_color(tex_y, ray);
		my_mlx_pixel_put(data->img_data, x, y, pixel_color);
	}
}

void	calculate_step_and_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (data->player->pos_x - ray->map_x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - data->player->pos_x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (data->player->pos_y - ray->map_y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - data->player->pos_y)
			* ray->delta_dist.y;
	}
}
