/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dup_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:29:02 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/21 16:39:22 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	path_recursive(char **map, int i, int j)
{
	if ((map[i][j] == '0' && map[i + 1][j] == '*') || (map[i][j] == '0' && map[i
			- 1][j] == '*') || (map[i][j] == '0' && map[i][j + 1] == '*')
		|| (map[i][j] == '0' && map[i][j - 1] == '*'))
		ft_err();
}

void	path_recursive2(char **map, int i, int j, char c)
{
	if ((map[i][j] == c && map[i + 1][j] == '*') || (map[i][j] == c && map[i
			- 1][j] == '*') || (map[i][j] == c && map[i][j + 1] == '*')
		|| (map[i][j] == c && map[i][j - 1] == '*'))
		ft_err();
}

void	path_checker(char **str, t_data *data)
{
	int	j;
	int	i;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '0' || str[i][j] == '1'))
				path_recursive(str, i, j);
			else if (str[i][j] == data->map.type)
				path_recursive2(str, i, j, data->map.type);
		}
	}
}

char	**duplicate_to_map(t_data *data)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (data->map.map_row + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (data->map.map2[i])
	{
		copy[i] = ft_strdup(data->map.map2[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ctrl(t_data *data)
{
	char	**str;
	int		i;
	int		a;
	size_t	tmp;

	str = data->map.map2;
	i = -1;
	tmp = 0;
	while (str[++i])
	{
		if (ft_strlen(str[i]) > tmp)
			a = ft_strlen(str[i]);
		tmp = a;
	}
	data->map.map_col = a;
}
