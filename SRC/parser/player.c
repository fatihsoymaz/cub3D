/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taybakan <taybakan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:53:33 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/10 00:10:00 by taybakan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
