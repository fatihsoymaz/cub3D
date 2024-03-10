/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ret.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:04:09 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 22:40:12 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_format(char *str)
{
	int	i;

	i = -1;
	while (str[i])
	{
		if (str[i] == ',' && (str[i - 1] == ' ' || str[i + 1] == ' '))
			ft_err();
		i++;
	}
}

char	**ft_ret_fc_next(char *str, char **split, char c)
{
	int	i;

	i = 0;
	while (ft_wh_sp(str[i]))
		i++;
	if (str[i] == c && str[i + 1] == 32)
	{
		i++;
		while (str[i] == 32)
			i++;
	}
	else
		ft_err();
	check_format(str + i);
	split = ft_split(str + i, ',');
	return (split);
}

int	*ft_ret_fc(char *str, char c)
{
	char	**split;
	int		*a;

	split = NULL;
	a = malloc(sizeof(int) * 3);
	split = ft_ret_fc_next(str, split, c);
	a[0] = ft_atoi(split[0]);
	a[1] = ft_atoi(split[1]);
	a[2] = ft_atoi(split[2]);
	if (a[0] > 255 || a[1] > 255 || a[2] > 255)
		ft_err();
	map_free(split);
	return (a);
}

char	*ft_ret(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i])
		if (str[i] == '.' && str[i - 1] != 32 && str[i + 1] == '/')
			ft_err();
	ret = ft_strtrim(str, " \n");
	return (ret);
}
