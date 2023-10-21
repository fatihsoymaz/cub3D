/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:56:00 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/21 12:57:37 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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