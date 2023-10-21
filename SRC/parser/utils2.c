/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:56:00 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/21 16:39:34 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	del_wspace(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != ' ')
		{
			(*str)[j] = (*str)[i];
			j++;
		}
		i++;
	}
	(*str)[j] = '\0';
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

void	free_func(t_data *data)
{
	int	i;

	i = -1;
	while (data->map.map2[++i])
		free(data->map.map2[i]);
	i = -1;
	free(data->map.map);
	free(data->map.map2);
	free(data->map.ea);
	free(data->map.so);
	free(data->map.no);
	free(data->map.we);
	free(data->map.f);
	free(data->map.c);
	free(data);
}

void	space_full(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (ft_wh_sp(str[i][j]))
				str[i][j] = '*';
		}
	}
}

void	empty_line(char **str, int *k, t_data *data)
{
	int	i;

	i = *k - 1;
	while (str[++i] && i < data->map.map_row - 1)
		if (str[i][0] == '\n' && (str[i + 1][0] == '1' || str[i + 1][0] == 32))
			ft_err();
}
