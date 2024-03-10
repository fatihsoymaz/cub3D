/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nswc_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:43:50 by fsoymaz           #+#    #+#             */
/*   Updated: 2024/03/09 21:05:18 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
