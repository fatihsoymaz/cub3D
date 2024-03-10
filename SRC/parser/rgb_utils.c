/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taybakan <taybakan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:22:58 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/10 00:12:48 by taybakan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	w_rgb_to_map(t_data *data)
{
	data->floor_color = (data->map.f[0] << 16) + (data->map.f[1] << 8)
		+ data->map.f[2];
	data->ceiling_color = (data->map.c[0] << 16) + (data->map.c[1] << 8)
		+ data->map.c[2];
}

void	wall_image(t_data *data)
{
	int	i;

	i = -1;
	data->img_data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_data->addr = mlx_get_data_addr(data->img_data->img,
			&data->img_data->bpp, &data->img_data->line_length,
			&data->img_data->endian);
	data->imgs[3].img = data->ea_img;
	data->imgs[1].img = data->so_img;
	data->imgs[2].img = data->no_img;
	data->imgs[0].img = data->we_img;
	while (++i < 4)
	{
		data->imgs[i].addr = mlx_get_data_addr(data->imgs[i].img,
				&data->imgs[i].bpp, &data->imgs[i].line_length,
				&data->imgs[i].endian);
	}
}
