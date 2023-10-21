/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nswc_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:43:50 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/21 16:39:27 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_comma(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == ',')
			count++;
		s++;
	}
	return (count);
}

int	add_count(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ',' || s[i] == ' ')
			i++;
		if (s[i] == '\n')
			break ;
		if (s[i])
			count++;
		while (s[i] && s[i] != ' ' && s[i] != ',')
			i++;
	}
	return (count);
}

int	count_wd(char *s)
{
	int	i;
	int	count;

	count = add_count(s);
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != ',' && s[i] != '\n' && s[i] != ' ')
			ft_err();
	del_wspace(&s);
	while (*s)
	{
		if (*s == ',' && ft_strchr(",\n", *(s + 1)))
			ft_err();
		s++;
	}
	return (count);
}

void	control2(t_data *data, char *str)
{
	int	i;

	i = -1;
	while (str[++i] == 32)
		;
	if (!ft_strncmp(str + i, "F", 1))
		data->map.f = ft_ret_fc(str + i, 'F');
	if (!ft_strncmp(str + i, "C", 1))
		data->map.c = ft_ret_fc(str + i, 'C');
}
