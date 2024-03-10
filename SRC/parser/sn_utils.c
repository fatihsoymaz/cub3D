/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:59:29 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 21:12:52 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_check_and_assign(char *str, char *direction, char **game_direction)
{
	if (!ft_strncmp(str, direction, 2))
	{
		if (*game_direction)
			ft_err();
		*game_direction = ft_ret(str + 2);
	}
}

void	ft_check2(char *str)
{
	if ((str[0] == 'W' && str[1] != 'E') || (str[0] == 'E' && str[1] != 'A')
		|| (str[0] == 'S' && str[1] != 'O') || (str[0] == 'N' && str[1] != 'O'))
		ft_err();
}

void	ft_nosw(char *str, t_data *game)
{
	while (*str == 32)
		str++;
	ft_check2(str);
	ft_check_and_assign(str, "NO", &(game->map.no));
	ft_check_and_assign(str, "SO", &(game->map.so));
	ft_check_and_assign(str, "WE", &(game->map.we));
	ft_check_and_assign(str, "EA", &(game->map.ea));
}
