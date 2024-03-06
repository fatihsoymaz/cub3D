/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:59:29 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/06 22:39:17 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_nosw_part2(char *str, t_data *game)
{
	if (!ft_strncmp(str, "WE", 2))
	{
		if (game->map.we)
			ft_err();
		game->map.we = ft_ret(str + 2);
	}
	else if (!ft_strncmp(str, "EA", 2))
	{
		if (game->map.ea)
			ft_err();
		game->map.ea = ft_ret(str + 2);
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
	if (!ft_strncmp(str, "NO", 2))
	{
		if (game->map.no)
			ft_err();
		game->map.no = ft_ret(str + 2);
	}
	else if (!ft_strncmp(str, "SO", 2))
	{
		if (game->map.so)
			ft_err();
		game->map.so = ft_ret(str + 2);
	}
	ft_nosw_part2(str, game);
}

void	empty_line(char **str, int *k, t_data *data)
{
	int	i;

	i = *k - 1;
	while (str[++i] && i < data->map.map_row - 1)
		if (str[i][0] == '\n' && (str[i + 1][0] == '1' || str[i + 1][0] == 32))
			ft_err();
}
