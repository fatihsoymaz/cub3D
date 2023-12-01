/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:39:47 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/12/01 15:09:55 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_change(char *str, t_data *data)
{
	char	*a;

	a = ft_strjoin_v2(str, '*', data->map.map_col);
	return (a);
}

char	*print_star(char **str, t_data *data)
{
	int		i;
	char	*s;

	s = *str;
	s = malloc(sizeof(char) * data->map.map_col + 3);
	i = 0;
	while (i < data->map.map_col)
	{
		s[i] = '*';
		i++;
	}
	s[i] = '*';
	s[i + 1] = '\0';
	return (s);
}

void	check_valid_map(char **map, t_data *data)
{
	int		i;
	char	**str;
	int		j;

	if (data->map.count != 1)
		ft_err();
	j = -1;
	i = 0;
	str = ft_calloc(sizeof(char *) * (data->map.map_row + 3), 1);
	str[0] = print_star(str, data);
	while (map[++j])
		str[++i] = ft_change(map[j], data);
	str[i + 1] = print_star(str, data);
	str[i + 2] = NULL;
	space_full(str);
	path_checker(str, data);
	map_free(map);
	map_free(str);
}

void	data_add_arg(t_data *data, int *i, int *j, int *k)
{
	while (data->map.map2[*i])
	{
		if (ft_sp_ctrl(data->map.map2[*i]) == 0)
		{
			ft_err();
		}
		*j = -1;
		while (data->map.map2[*i][++(*j)])
		{
			if (!ft_strchr("01\nNSWE ", data->map.map2[*i][*j]))
				ft_err();
			else if (ft_strchr("NWES", data->map.map2[*i][*j]))
			{
				data->map.type = data->map.map2[*i][*j];
				data->map.count++;
				data->map.p_row = (double)*i - (double)*k;
				data->map.p_col = (double)*j;
			}
		}
		(*i)++;
	}
}

void	ft_get_map2(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (ft_strlen(data->map.map2[i]) == 1)
		i++;
	empty_line(data->map.map2, &i, data);
	k = i;
	data_add_arg(data, &i, &k, &j);
	ctrl(data);
	check_valid_map(duplicate_to_map(data), data);
}
