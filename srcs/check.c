/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:50:14 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/02 16:54:29 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_cub(const char *str)
{
	int	size;

	size = ft_strlen((char *)str);
	if (str[size - 1] == 'b' && str[size - 2] == 'u')
	{
		if (str[size - 3] == 'c' || str[size - 4] == '.')
			return ;
	}
	ft_printf("Error : File not .cub\n");
	exit(-1);
}