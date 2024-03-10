/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:04:52 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 23:02:57 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	return (data->map.map2[(int)(new_y)][(int)(new_x)] == '1');
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
