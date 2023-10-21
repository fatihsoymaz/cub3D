/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:39:47 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/21 12:41:22 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

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

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0' || str[i][j] == '1')
				path_recursive(str, i, j);
			else if (str[i][j] == data->map.type)
				path_recursive2(str, i, j, data->map.type);
			j++;
		}
		i++;
	}

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

void	check_valid_map(char **map, t_data *data)
{
	int		i;
	char	**str;
	int		j;

	j = 0;
	i = 0;
	str = ft_calloc(sizeof(char *) * (data->map.map_row + 3), 1);
	str[0] = print_star(str, data);
	while (map[j])
	{
		str[++i] = ft_change(map[j], data);
		j++;
	}
	str[i + 1] = print_star(str, data);
	str[i + 2] = NULL;
	space_full(str);
	path_checker(str, data);
	printmap(str);
	map_free(map);
	map_free(str);
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

void	empty_line(char **str, int *k, t_data *data)
{
	int	i;

	i = *k;
	while (str[i] && i < data->map.map_row - 1)
	{
		if (str[i][0] == '\n' && str[i + 1][0] != '\n')
			ft_err();
		i++;
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
	while (data->map.map2[i])
	{
		if (ft_sp_ctrl(data->map.map2[i]) == 0)
			ft_err();
		j = -1;
		while (data->map.map2[i][++j])
		{
			if (!ft_strchr("01\n NSWE", data->map.map2[i][j]))
				ft_err();

			if (ft_strchr("NWES", data->map.map2[i][j]))
			{
				data->map.type = data->map.map2[i][j];
				data->map.count++;
				data->map.p_row = (double)i - (double)k;
				data->map.p_col = (double)j;
			}
		}
		i++;
	}
	if (data->map.count != 1)
		ft_err();	
	ctrl(data);

	check_valid_map(duplicate_to_map(data), data);
}
