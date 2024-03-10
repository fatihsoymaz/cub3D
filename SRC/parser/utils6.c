/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:14:29 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 23:28:38 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fix_mirror(t_ray *ray)
{
	if ((ray->side == 0 && ray->ray_dir.x < 0) || (ray->side == 1
			&& ray->ray_dir.y > 0))
		ray->tex_x = 64 - ray->tex_x - 1;
}

int	safe_divide(int numerator, double denominator)
{
	if (denominator < 0.00001)
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

int	get_tex_y(int y, int line_height)
{
	double	half_screen_height;
	double	half_line_height;
	double	tmp;

	half_screen_height = HEIGHT / 2.0;
	half_line_height = line_height / 2.0;
	tmp = (y - half_screen_height + half_line_height);
	tmp *= (double)(64) / line_height;
	return ((int)tmp);
}

unsigned int	get_pixel_color(int tex_y, t_ray *ray)
{
	int	texture_byte_size;
	int	texture_offset;

	texture_byte_size = ray->img->bpp / 8;
	texture_offset = (tex_y * ray->img->line_length) + ray->tex_x
		* texture_byte_size;
	return (*(unsigned int *)(ray->img->addr + texture_offset));
}
