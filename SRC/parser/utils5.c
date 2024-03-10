/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:12:51 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/10 11:55:43 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	is_boundary_violated(t_ray *ray, int map_size)
{
	return (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= map_size
		|| ray->map_y >= map_size);
}

int	is_hit(t_ray *ray, t_data *data)
{
	return (is_boundary_violated(ray, WIDTH)
		|| data->map.map2[ray->map_y][ray->map_x] == '1');
}

void	determine_texture(t_data *data, t_ray *ray)
{
	if (ray->side == EAST_WEST)
	{
		if (ray->ray_dir.x > 0)
			ray->img = (&data->imgs[3]);
		else
			ray->img = (&data->imgs[0]);
	}
	else
	{
		if (ray->ray_dir.y > 0)
			ray->img = (&data->imgs[1]);
		else
			ray->img = (&data->imgs[2]);
	}
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
