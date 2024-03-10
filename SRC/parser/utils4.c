/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:09:22 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 23:29:04 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 17, 0, close_window, NULL);
	mlx_hook(data->mlx_win, 2, 0, ft_press, data);
	mlx_hook(data->mlx_win, 3, 0, ft_release, data);
	mlx_loop_hook(data->mlx, render, data);
}

int	ft_sp_ctrl(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != 32)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (str[i] == '\n' && ft_strlen(str) == 1)
		flag = 1;
	return (flag);
}
